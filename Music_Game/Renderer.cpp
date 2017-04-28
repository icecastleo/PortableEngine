//Darren Farr
#include "Renderer.h"

using namespace DirectX;

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Renderer::Renderer()
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;
}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
Renderer::~Renderer() 
{
	ppSRV->Release();
	ppRTV->Release();

	delete blur;
}

//---------------------------------------------------------
//Inititialize one time members
//---------------------------------------------------------
void Renderer::Init(Camera* _Cam, ID3D11Device* device, ID3D11DeviceContext* con, ID3D11RenderTargetView* tView, IDXGISwapChain* chain, ID3D11DepthStencilView* depth, unsigned int width, unsigned int height)
{
	Cam = _Cam;
	mDevice = device;
	context = con;
	backBufferRTV = tView;
	swapChain = chain;
	depthStencilView = depth;

	mWidth = width;
	mHeight = height;

	// Create post process resources -----------------------------------------
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = mWidth;
	textureDesc.Height = mHeight;
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* ppTexture;
	device->CreateTexture2D(&textureDesc, 0, &ppTexture);

	// Create the Render Target View
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.Texture2D.MipSlice = 0;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	device->CreateRenderTargetView(ppTexture, &rtvDesc, &ppRTV);

	// Create the Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	device->CreateShaderResourceView(ppTexture, &srvDesc, &ppSRV);

	// We don't need the texture reference itself no mo'
	ppTexture->Release();

	blur = new GaussianBlur(mDevice, context);
	blur->Init(mWidth, mHeight, depthStencilView);

	bloom = new Bloom(mDevice, context);
	bloom->Init(mWidth, mHeight, depthStencilView);
}

//---------------------------------------------------------
//Set Shaders
//---------------------------------------------------------
void Renderer::SetShaders(SimpleVertexShader* _vertexShader, SimplePixelShader* _pixelShader, 
	SimpleVertexShader* _vertShaderNorm, SimplePixelShader* _pixShaderNorm, SimpleVertexShader* _skyVs, SimplePixelShader* _skyPs)
{
	vertexShader = _vertexShader;
	pixelShader = _pixelShader;
	vertexShaderNormalMap = _vertShaderNorm;
	pixelShaderNormalMap = _pixShaderNorm;
	skyVS = _skyVs;
	skyPS = _skyPs;
}

//---------------------------------------------------------
//Set Entities
//---------------------------------------------------------
void Renderer::SetScene(Scene* _scene)
{
	currentScene = _scene;
}

//---------------------------------------------------------
//Draw
//Intitial code from original game.cpp - Chris Cascioli
//Rewritten to work with a list of entities
//---------------------------------------------------------
void Renderer::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	//context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Post process initial setup =================
	// Start rendering somewhere else!
	context->ClearRenderTargetView(ppRTV, color);
	context->OMSetRenderTargets(1, &ppRTV, depthStencilView);

	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	currentScene->name = "d";
	//Loop through the list of Entities and draw each one
	for (unsigned i = 0; i < currentScene->entities.size(); i++)
	{
		//call to set shaders goes here
		if (currentScene->entities.at(i)->GetMat()->HasNormalMap())
		{
			currentScene->entities.at(i)->GetMat()->PrepareMaterial(currentScene->entities.at(i)->GetWorldMat(), Cam->GetViewMatrix(), Cam->GetProjectionMatrix(), vertexShaderNormalMap);
			SetPixelShaderUp(pixelShaderNormalMap, i);
		}
		else
		{
			currentScene->entities.at(i)->GetMat()->PrepareMaterial(currentScene->entities.at(i)->GetWorldMat(), Cam->GetViewMatrix(), Cam->GetProjectionMatrix(), vertexShader);
			SetPixelShaderUp(pixelShader, i);
		}

		stride = sizeof(Vertex);
		offset = 0;

		vertexBuffer = currentScene->entities.at(i)->GetMesh()->GetVertexBuffer(); //Store the vertex buffer address
		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(currentScene->entities.at(i)->GetMesh()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		// Finally do the actual drawing
		//  - Do this ONCE PER OBJECT you intend to draw
		//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
		//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
		//     vertices in the currently set VERTEX BUFFER
		context->DrawIndexed(
			currentScene->entities.at(i)->GetMesh()->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	}

	if (currentScene->background != NULL)
	{
		vertexBuffer = currentScene->background->GetMesh()->GetVertexBuffer();
		indexBuffer = currentScene->background->GetMesh()->GetIndexBuffer();

		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		currentScene->background->GetMat()->PrepareSkybox(Cam->GetViewMatrix(), Cam->GetProjectionMatrix(), skyVS, skyPS);

		context->RSSetState(currentScene->background->GetMat()->GetRast());
		context->OMSetDepthStencilState(currentScene->background->GetMat()->GetDepthSD(), 0);
		context->DrawIndexed(currentScene->background->GetMesh()->GetIndexCount(), 0, 0);

		// Reset the render states we've changed
		context->RSSetState(0);
		context->OMSetDepthStencilState(0, 0);
	}

	//blur->Draw(deltaTime, ppSRV, backBufferRTV);
	bloom->Draw(deltaTime, ppSRV, backBufferRTV);

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}

//---------------------------------------------------------
//Set the pixel shader up
//---------------------------------------------------------
void Renderer::SetPixelShaderUp(SimplePixelShader* pShader, int i)
{
	pShader->SetFloat4("camPos", Cam->GetPositon());

	if (currentScene->spotLights.size() > 0) {
		currentScene->spotLights.at(0)->Direction.x = Cam->GetDirection().x;
		currentScene->spotLights.at(0)->Direction.y = Cam->GetDirection().y;
		currentScene->spotLights.at(0)->Direction.z = Cam->GetDirection().z;
		currentScene->spotLights.at(0)->Position.x = Cam->GetPositon().x;
		currentScene->spotLights.at(0)->Position.y = Cam->GetPositon().y;
		currentScene->spotLights.at(0)->Position.z = Cam->GetPositon().z;
	}

	//loop through lights
	//global lights
	for (int g = 0; g < currentScene->globalLights.size(); g++)
	{
		std::string name = "ambient" + std::to_string(g);
		//setup lights
		pShader->SetData(
			name,
			currentScene->globalLights.at(g),
			sizeof(GlobalLight)
		);
	}

	//directional lights
	for (int d = 0; d < currentScene->directionalLights.size(); d++)
	{
		std::string name = "light" + std::to_string(d);
		//setup lights
		pShader->SetData(
			name,
			currentScene->directionalLights.at(d),
			sizeof(DirectionalLight)
		);
	}

	//point lights
	for (int p = 0; p < currentScene->pointLights.size(); p++)
	{
		std::string name = "lightP" + std::to_string(p);
		//setup lights
		pShader->SetData(
			name,
			currentScene->pointLights.at(p),
			sizeof(PointLight)
		);
	}

	//spot lights
	for (int s = 0; s < currentScene->spotLights.size(); s++)
	{
		std::string name = "lightS" + std::to_string(s);
		//setup lights
		pShader->SetData(
			name,
			currentScene->spotLights.at(s),
			sizeof(SpotLight)
		);
	}

	pShader->SetSamplerState("basicSampler", currentScene->entities.at(i)->GetMat()->GetSampleState());
	pShader->SetShaderResourceView("diffuseTexture", currentScene->entities.at(i)->GetMat()->GetSRV());

	//check for a normal map
	if (currentScene->entities.at(i)->GetMat()->HasNormalMap())
	{
		pShader->SetShaderResourceView("NormalMap", currentScene->entities.at(i)->GetMat()->GetNormalSRV());
	}

	if (currentScene->background != NULL)
	{
		pShader->SetShaderResourceView("Sky", currentScene->background->GetMat()->GetSkySRV());
	}

	pShader->CopyAllBufferData();

	pShader->SetShader();
}

//---------------------------------------------------------
//Update the depth Stencil View
//Program Errors on window resize if this is not updated
//---------------------------------------------------------
void Renderer::Resized(ID3D11DepthStencilView* depth, ID3D11RenderTargetView* bBRTV, unsigned int width, unsigned int height)
{
	depthStencilView = depth;
	backBufferRTV = bBRTV;
	mWidth = width;
	mHeight = height;

	blur->Resize(width, height, depthStencilView);
	bloom->Resize(width, height, depthStencilView);
}