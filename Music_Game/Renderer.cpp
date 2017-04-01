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
Renderer::~Renderer() {}

//---------------------------------------------------------
//Inititialize one time members
//---------------------------------------------------------
void Renderer::Init(Camera* _Cam, ID3D11DeviceContext* con, ID3D11RenderTargetView* tView, IDXGISwapChain* chain, ID3D11DepthStencilView* depth)
{
	Cam = _Cam;
	context = con;
	backBufferRTV = tView;
	swapChain = chain;
	depthStencilView = depth;
}

//---------------------------------------------------------
//Set Shaders
//---------------------------------------------------------
void Renderer::SetShaders(SimpleVertexShader* _vertexShader, SimplePixelShader* _pixelShader, SimpleVertexShader* _skyVs, SimplePixelShader* _skyPs)
{
	vertexShader = _vertexShader;
	pixelShader = _pixelShader;
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
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

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
		currentScene->entities.at(i)->GetMat()->PrepareMaterial(currentScene->entities.at(i)->GetWorldMat(), Cam->GetViewMatrix(), Cam->GetProjectionMatrix(), vertexShader);

		pixelShader->SetFloat4("camPos", Cam->GetPositon());

		if (currentScene->spotLights.size() > 0) {
			currentScene->spotLights.at(0)->Direction.x = Cam->GetDirection().x;
			currentScene->spotLights.at(0)->Direction.y = Cam->GetDirection().y;
			currentScene->spotLights.at(0)->Direction.z = Cam->GetDirection().z;
			currentScene->spotLights.at(0)->Position.x = Cam->GetPositon().x;
			currentScene->spotLights.at(0)->Position.y = Cam->GetPositon().y;
			currentScene->spotLights.at(0)->Position.z = Cam->GetPositon().z;
		}

		//loop through lights
		for (int g = 0; g < currentScene->globalLights.size(); g++)
		{
			std::string name = "ambient" + std::to_string(g);
			//setup lights
			pixelShader->SetData(
				name,
				currentScene->globalLights.at(g),
				sizeof(GlobalLight)
			);
		}

		for (int l = 0; l < currentScene->directionalLights.size(); l++)
		{
			std::string name = "light" + std::to_string(l);
			//setup lights
			pixelShader->SetData(
				name,
				currentScene->directionalLights.at(l),
				sizeof(DirectionalLight)
			);
		}

		for (int p = 0; p < currentScene->pointLights.size(); p++)
		{
			std::string name = "lightP" + std::to_string(p);
			//setup lights
			pixelShader->SetData(
				name,
				currentScene->pointLights.at(p),
				sizeof(PointLight)
			);
		}

		for (int s = 0; s < currentScene->spotLights.size(); s++)
		{
			std::string name = "lightS" + std::to_string(s);
			//setup lights
			pixelShader->SetData(
				name,
				currentScene->spotLights.at(s),
				sizeof(SpotLight)
			);
		}
		
		pixelShader->SetSamplerState("basicSampler", currentScene->entities.at(i)->GetMat()->GetSampleState());
		pixelShader->SetShaderResourceView("diffuseTexture", currentScene->entities.at(i)->GetMat()->GetSRV());
		if (currentScene->background != NULL)
		{
			pixelShader->SetShaderResourceView("Sky", currentScene->background->GetMat()->GetSkySRV());
		}

		pixelShader->CopyAllBufferData();

		pixelShader->SetShader();

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

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


//---------------------------------------------------------
//Update the depth Stencil View
//Program Errors on window resize if this is not updated
//---------------------------------------------------------
void Renderer::Resized(ID3D11DepthStencilView* depth, ID3D11RenderTargetView* bBRTV)
{
	depthStencilView = depth;
	backBufferRTV = bBRTV;
}