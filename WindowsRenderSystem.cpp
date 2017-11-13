
#include "WindowsRenderSystem.h"
#include <time.h> 
#include <iostream>
#include "WindowsCamera.h"
#include "Engine.h"
#include "PC_IOSystem.h"

WindowsRenderSystem::WindowsRenderSystem(uint16_t width, uint16_t height, HWND hWnd)					
{
	this->hWnd = hWnd;

	device = 0;
	context = 0;
	swapChain = 0;
	backBufferRTV = 0;
	depthStencilView = 0;

	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;
	vertexShaderNormalMap = 0;
	pixelShaderNormalMap = 0;
	pixelShaderBlend = 0;
	pixelShaderNormalMapBlend = 0;

	camera = new WindowsCamera(width, height);

	HRESULT hr = InitDirectX(width, height);
	if (FAILED(hr)) {
		perror("Failed to init DirectX \n");
	}
}

/** 
	Destructor - Clean up anything our game has created:
	Release all DirectX objects created here
	Delete any objects to prevent memory leaks
*/ 
WindowsRenderSystem::~WindowsRenderSystem()
{
	// Release all DirectX resources
	if (depthStencilView) { depthStencilView->Release(); }
	if (backBufferRTV) { backBufferRTV->Release(); }

	if (swapChain) { swapChain->Release(); }
	if (context) { context->Release(); }

	//#if defined (DEBUG) | defined (_DEBUG)
	//	HRESULT hr = S_OK;
	//
	//	ID3D11Debug * DebugDevice = nullptr;
	//	hr = device->QueryInterface(__uuidof(ID3D11Debug), static_cast<void**>(&DebugDevice));
	//	//if (FAILED(hr)) return hr;
	//
	//	hr = DebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//	//if (FAILED(hr)) return hr;
	//
	//	DebugDevice->Release();
	//#endif

	if (device)
		device->Release();

	delete camera;
}

// --------------------------------------------------------
// Called once per program, after the window
// are initialized but before the game loop.
// --------------------------------------------------------
void WindowsRenderSystem::Init(uint16_t width, uint16_t height)
{
	LoadShaders();
	GetShaders();

	Render.SetShaders(vertexShader, pixelShader, vertexShaderNormalMap, pixelShaderNormalMap, skyVS, skyPS,
		pixelShaderBlend, pixelShaderNormalMapBlend);

	Render.Init(camera, device, context, backBufferRTV, swapChain, depthStencilView, width, height);

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Initializes DirectX, which requires a window.  This method
// also creates several DirectX objects we'll need to start
// drawing things to the screen.
// --------------------------------------------------------
HRESULT WindowsRenderSystem::InitDirectX(uint16_t width, uint16_t height)
{
	// This will hold options for DirectX initialization
	unsigned int deviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// If we're in debug mode in visual studio, we also
	// want to make a "Debug DirectX Device" to see some
	// errors and warnings in Visual Studio's output window
	// when things go wrong!
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create a description of how our swap
	// chain should work
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.Flags = 0;
	swapDesc.OutputWindow = hWnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;

	// Result variable for below function calls
	HRESULT hr = S_OK;

	// Attempt to initialize DirectX
	hr = D3D11CreateDeviceAndSwapChain(
		0,							// Video adapter (physical GPU) to use, or null for default
		D3D_DRIVER_TYPE_HARDWARE,	// We want to use the hardware (GPU)
		0,							// Used when doing software rendering
		deviceFlags,				// Any special options
		0,							// Optional array of possible verisons we want as fallbacks
		0,							// The number of fallbacks in the above param
		D3D11_SDK_VERSION,			// Current version of the SDK
		&swapDesc,					// Address of swap chain options
		&swapChain,					// Pointer to our Swap Chain pointer
		&device,					// Pointer to our Device pointer
		&dxFeatureLevel,			// This will hold the actual feature level the app will use
		&context);					// Pointer to our Device Context pointer
	if (FAILED(hr)) return hr;

	// The above function created the back buffer render target
	// for us, but we need a reference to it
	ID3D11Texture2D* backBufferTexture;
	swapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBufferTexture);

	// Now that we have the texture, create a render target view
	// for the back buffer so we can render into it.  Then release
	// our local reference to the texture, since we have the view.
	device->CreateRenderTargetView(
		backBufferTexture,
		0,
		&backBufferRTV);
	backBufferTexture->Release();

	// Set up the description of the texture to use for the depth buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	// Create the depth buffer and its view, then 
	// release our reference to the texture
	ID3D11Texture2D* depthBufferTexture;
	device->CreateTexture2D(&depthStencilDesc, 0, &depthBufferTexture);
	device->CreateDepthStencilView(depthBufferTexture, 0, &depthStencilView);
	depthBufferTexture->Release();

	// Bind the views to the pipeline, so rendering properly 
	// uses their underlying textures
	context->OMSetRenderTargets(1, &backBufferRTV, depthStencilView);

	// Lastly, set up a viewport so we render into
	// to correct portion of the window
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	// Return the "everything is ok" HRESULT value
	return S_OK;
}

ID3D11Device * WindowsRenderSystem::GetDevice()
{
	return device;
}

ID3D11DeviceContext * WindowsRenderSystem::GetContext()
{
	return context;
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void WindowsRenderSystem::LoadShaders()
{
	const wchar_t * name;
	name = L"VertexShader";
	   Engine::ioSystem->loadVSShader(name);

	name = L"PixelShader";
	   Engine::ioSystem->loadPSShader(name);

	name = L"VertexShaderNormalMap";
		Engine::ioSystem->loadVSShader(name);

	name = L"PixelShaderNormalMap";
		Engine::ioSystem->loadPSShader(name);
	
	name = L"SkyVS";
		Engine::ioSystem->loadVSShader(name);

	name = L"SkyPS";
		Engine::ioSystem->loadPSShader(name);

	name = L"BlendPixelShader";
		Engine::ioSystem->loadPSShader(name);

	name = L"PixelShaderNormalMapBlend"; 
		Engine::ioSystem->loadPSShader(name);
}

void WindowsRenderSystem::GetShaders() {
	const wchar_t * name;
	name = L"VertexShader";
	vertexShader = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getVertexShader(name);

	name = L"PixelShader";
	pixelShader = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getPixelShader(name);

	name = L"VertexShaderNormalMap";
	vertexShaderNormalMap = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getVertexShader(name);

	name = L"PixelShaderNormalMap";
	pixelShaderNormalMap = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getPixelShader(name);

	name = L"SkyVS";
	skyVS = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getVertexShader(name);

	name = L"SkyPS";
	skyPS = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getPixelShader(name);

	name = L"BlendPixelShader";
	pixelShaderBlend = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getPixelShader(name);

	name = L"PixelShaderNormalMapBlend";
	pixelShaderNormalMapBlend = (static_cast<PC_IOSystem *>(Engine::ioSystem))->getPixelShader(name);
}

void WindowsRenderSystem::SetScene(Scene *scene)
{
	RenderSystem::SetScene(scene);

	Render.SetScene(scene);

	musicPlayer.stop();

	if (scene->musicFileName) {
		musicPlayer.setSound(scene->musicFileName);
		musicPlayer.play();
	}
}

// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void WindowsRenderSystem::OnResize(uint16_t width, uint16_t height)
{ 
	RenderSystem::OnResize(width, height);

	// Release existing DirectX views and buffers
	if (depthStencilView) { depthStencilView->Release(); }
	if (backBufferRTV) { backBufferRTV->Release(); }

	// Resize the underlying swap chain buffers
	swapChain->ResizeBuffers(
		1,
		width,
		height,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0);

	// Recreate the render target view for the back buffer
	// texture, then release our local texture reference
	ID3D11Texture2D* backBufferTexture;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTexture));
	device->CreateRenderTargetView(backBufferTexture, 0, &backBufferRTV);
	backBufferTexture->Release();

	// Set up the description of the texture to use for the depth buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	// Create the depth buffer and its view, then 
	// release our reference to the texture
	ID3D11Texture2D* depthBufferTexture;
	device->CreateTexture2D(&depthStencilDesc, 0, &depthBufferTexture);
	device->CreateDepthStencilView(depthBufferTexture, 0, &depthStencilView);
	depthBufferTexture->Release();

	// Bind the views to the pipeline, so rendering properly 
	// uses their underlying textures
	context->OMSetRenderTargets(1, &backBufferRTV, depthStencilView);

	// Lastly, set up a viewport so we render into
	// to correct portion of the window
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	Render.Resized(depthStencilView, backBufferRTV, width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void WindowsRenderSystem::Update(float deltaTime)
{
	RenderSystem::Update(deltaTime);

	//If in scene 1 go to scene 2
	if (GetAsyncKeyState(VK_RETURN))
	{
		////Need to insert a time delay before scene may change again
		//if (totalTime > sceneChangeTime + 2)
		//{
		//	sceneChangeTime = totalTime;
		//	SceneNumber = (SceneNumber % SceneManag.GetNumOfScenes()) + 1;
		//	setScene();
		//}

		/*static float updateTemp = 0;

		updateTemp += deltaTime;

		if (updateTemp > 0.5f) {
			updateTemp -= 0.5f;
			SceneNumber = (SceneNumber % SceneManag.GetNumOfScenes()) + 1;
			setScene();
		}*/
	}

	musicPlayer.update();
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void WindowsRenderSystem::Draw()
{
	Render.Draw();
}
