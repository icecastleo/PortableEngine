#include "Renderer.h"
#include "D3D11Material.h"

Renderer::Renderer()
{
	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;

	ppRTV = 0;
	ppSRV = 0;
}

Renderer::~Renderer() 
{
	ppSRV->Release();
	ppRTV->Release();
	bsAlphaBlend->Release();
	rsNoCull->Release();

	delete blur;
	delete bloom;
}

//---------------------------------------------------------
//Inititialize one time members
//---------------------------------------------------------
void Renderer::Init(Camera* _Cam, ID3D11Device* device, ID3D11DeviceContext* con, ID3D11RenderTargetView* tView, 
	IDXGISwapChain* chain, ID3D11DepthStencilView* depthStencilView, unsigned int width, unsigned int height)
{
	camera = _Cam;
	mDevice = device;
	context = con;
	backBufferRTV = tView;
	swapChain = chain;
	context->RSGetState(&defaultState);

	setWidthHeight(width, height, depthStencilView);

	blur = new GaussianBlur(mDevice, context);
	blur->Init(width, height, depthStencilView);

	bloom = new Bloom(mDevice, context);
	bloom->Init(width, height, depthStencilView);

	CreateAdditionalRSStates();
}

void Renderer::SetShaders(SimpleVertexShader* _vertexShader, SimplePixelShader* _pixelShader,
	SimpleVertexShader* _vertShaderNorm, SimplePixelShader* _pixShaderNorm, SimpleVertexShader* _skyVs,
	SimplePixelShader* _skyPs, SimplePixelShader* _pixelShaderB, SimplePixelShader* _pixShaderNormB)
{
	vertexShader = _vertexShader;
	pixelShader = _pixelShader;
	vertexShaderNormalMap = _vertShaderNorm;
	pixelShaderNormalMap = _pixShaderNorm;
	skyVS = _skyVs;
	skyPS = _skyPs;
	pixelShaderBlend = _pixelShaderB;
	pixelShaderNormalMapBlend = _pixShaderNormB;
}

void Renderer::SetScene(Scene* _scene)
{
	currentScene = _scene;
}

void Renderer::Draw()
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	//context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearRenderTargetView(ppRTV, color);
	context->OMSetRenderTargets(1, &ppRTV, mDepthStencilView);

	context->ClearDepthStencilView(
		mDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	//Change render state back to defualt
	context->RSSetState(defaultState);

	// Turn off our custom blend state
	context->OMSetBlendState(nullptr, 0, 0xFFFFFFFF);

	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	D3D11Material *material;

	SimpleVertexShader *vShader;
	SimplePixelShader *pShader;

	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;

	//Draw opaque entities first then opaque with normals then transparent with normals and finally transparent objects
	for (Entity *entity : currentScene->opaque)
	{
		material = static_cast<D3D11Material*>(entity->GetMat());

		if (material->HasNormalMap()) {
			vShader = vertexShaderNormalMap;
			pShader = pixelShaderNormalMap;
		}
		else {
			vShader = vertexShader;
			pShader = pixelShader;
		}

		material->PrepareMaterial(entity->GetWorldMat(), camera->GetViewMatrix(), camera->GetProjectionMatrix(), vShader, pShader);
		SetPixelShaderUp(pShader, material);

		stride = sizeof(Vertex);
		offset = 0;

		vertexBuffer = static_cast<ID3D11Buffer*>(entity->GetMesh()->GetVertexBuffer()); //Store the vertex buffer address

		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(static_cast<ID3D11Buffer*>(entity->GetMesh()->GetIndexBuffer()), DXGI_FORMAT_R16_UINT, 0);

		// Finally do the actual drawing
		//  - Do this ONCE PER OBJECT you intend to draw
		//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
		//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
		//     vertices in the currently set VERTEX BUFFER
		context->DrawIndexed(
			entity->GetMesh()->GetIndices().size(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	}

	// draw skybox
	if (currentScene->skybox)
	{
		Entity *entity = currentScene->skybox;

		vertexBuffer = static_cast<ID3D11Buffer*>(entity->GetMesh()->GetVertexBuffer());
		
		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(static_cast<ID3D11Buffer*>(entity->GetMesh()->GetIndexBuffer()), DXGI_FORMAT_R16_UINT, 0);

		static_cast<D3D11Material *>(entity->GetMat())->PrepareMaterial(entity->GetWorldMat(), camera->GetViewMatrix(), camera->GetProjectionMatrix(), skyVS, skyPS);

		context->RSSetState(static_cast<D3D11Material *>(entity->GetMat())->GetRast());
		context->OMSetDepthStencilState(static_cast<D3D11Material *>(entity->GetMat())->GetDepthSD(), 0);
		context->DrawIndexed(currentScene->skybox->GetMesh()->GetIndices().size(), 0, 0);

		// Reset the render states we've changed
		context->RSSetState(0);
		context->OMSetDepthStencilState(0, 0);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------
	//Change render states based on blending/transperancy
	//Turn off back face culling
	context->RSSetState(rsNoCull);

	// Turn on our custom blend state to enable alpha blending
	context->OMSetBlendState(
		bsAlphaBlend,
		0, // Not using per-channel blend factors
		0xFFFFFFFF); // Sample mask - Need all bits set (0xFFFFFFFF)

	for (Entity *entity : currentScene->transparent)
	{
		material = static_cast<D3D11Material*>(entity->GetMat());

		if (material->HasNormalMap()) {
			vShader = vertexShaderNormalMap;
			pShader = pixelShaderNormalMapBlend;
		}
		else {
			vShader = vertexShader;
			pShader = pixelShaderBlend;
		}

		material->PrepareMaterial(entity->GetWorldMat(), camera->GetViewMatrix(), camera->GetProjectionMatrix(), vShader, pShader);
		SetPixelShaderUp(pShader, material);

		stride = sizeof(Vertex);
		offset = 0;

		vertexBuffer = static_cast<ID3D11Buffer*>(entity->GetMesh()->GetVertexBuffer()); //Store the vertex buffer address
		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(static_cast<ID3D11Buffer*>(entity->GetMesh()->GetIndexBuffer()), DXGI_FORMAT_R16_UINT, 0);

		context->DrawIndexed(
			entity->GetMesh()->GetIndices().size(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	}

	// Reset states to properly render next frame
	context->RSSetState(0);
	context->OMSetDepthStencilState(0, 0);
	float factors[4] = { 1,1,1,1 };
	context->OMSetBlendState(0, factors, 0xFFFFFFFF);

	// Render post process to backBuffer
	//blur->Draw(deltaTime, ppSRV, backBufferRTV);
	bloom->Draw(ppSRV, backBufferRTV);

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}

void Renderer::setWidthHeight(unsigned int width, unsigned int height, ID3D11DepthStencilView * depthStencilView)
{
	mDepthStencilView = depthStencilView;

	if (ppRTV) { ppRTV->Release(); }
	if (ppSRV) { ppSRV->Release(); }

	// Create post process resources
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
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
	mDevice->CreateTexture2D(&textureDesc, 0, &ppTexture);

	// Create the Render Target View
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.Texture2D.MipSlice = 0;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	mDevice->CreateRenderTargetView(ppTexture, &rtvDesc, &ppRTV);

	// Create the Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	mDevice->CreateShaderResourceView(ppTexture, &srvDesc, &ppSRV);

	// We don't need the texture reference itself no mo'
	ppTexture->Release();
}

void Renderer::SetPixelShaderUp(SimplePixelShader* pShader, D3D11Material *material)
{
	pShader->SetFloat3("cameraPosition", camera->GetPositon());

	if (currentScene->spotLights.size() > 0) {
		currentScene->spotLights.at(0)->Position = camera->GetPositon();
		currentScene->spotLights.at(0)->Direction = camera->GetDirection();
	}

	//loop through lights
	//global lights
	for (unsigned int g = 0; g < currentScene->globalLights.size(); g++)
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
	for (unsigned int d = 0; d < currentScene->directionalLights.size(); d++)
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
	for (unsigned int p = 0; p < currentScene->pointLights.size(); p++)
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
	for (unsigned int s = 0; s < currentScene->spotLights.size(); s++)
	{
		std::string name = "lightS" + std::to_string(s);
		//setup lights
		pShader->SetData(
			name,
			currentScene->spotLights.at(s),
			sizeof(SpotLight)
		);
	}

	pShader->SetSamplerState("basicSampler", material->GetSampleState());
	pShader->SetShaderResourceView("diffuseTexture", material->GetSRV());

	if (material->HasNormalMap()) {
		pShader->SetShaderResourceView("NormalMap", static_cast<ID3D11ShaderResourceView*>(material->GetNormalSRV()));
	}

	if (currentScene->skybox) {
		pShader->SetShaderResourceView("Sky", static_cast<D3D11Material *>(currentScene->skybox->GetMat())->GetSRV());
	}

	pShader->CopyAllBufferData();
	pShader->SetShader();
}

//---------------------------------------------------------
//Create additional render states
//---------------------------------------------------------
void Renderer::CreateAdditionalRSStates()
{
	// Set up a rasterizer state with no culling
	D3D11_RASTERIZER_DESC rd = {};
	rd.CullMode = D3D11_CULL_NONE;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.DepthClipEnable = true;
	mDevice->CreateRasterizerState(&rd, &rsNoCull);

	D3D11_BLEND_DESC bd = {};
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	mDevice->CreateBlendState(&bd, &bsAlphaBlend);
}


//---------------------------------------------------------
//Update the depth Stencil View
//Program Errors on window resize if this is not updated
//---------------------------------------------------------
void Renderer::Resized(ID3D11DepthStencilView* depthStencilView, ID3D11RenderTargetView* bBRTV, unsigned int width, unsigned int height)
{
	backBufferRTV = bBRTV;

	setWidthHeight(width, height, depthStencilView);

	blur->Resize(width, height, depthStencilView);
	bloom->Resize(width, height, depthStencilView);
}