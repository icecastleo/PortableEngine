//Original code - Chris Cascioli
//Modified for use in homework
#pragma once

#include "RenderSystem.h"
#include "D3D11.h"
#include "SimpleShader.h"
#include "Renderer.h"
#include "MusicPlayer.h"
#include <vector>

// We can include the correct library files here
// instead of in Visual Studio settings if we want
#pragma comment(lib, "d3d11.lib")


class WindowsRenderSystem
	: public RenderSystem
{

public:
	WindowsRenderSystem(uint16_t width, uint16_t height, HWND hWnd);
	~WindowsRenderSystem();
	void Init(uint16_t width, uint16_t height);

	void OnResize(uint16_t width, uint16_t height) override;
	void Update(float deltaTime) override;
	void Draw() override;

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void SetScene(Scene *scene);
	
private:
	HRESULT InitDirectX(uint16_t width, uint16_t height);

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders();
	void GetShaders();

	HWND hWnd;					// The handle to the window itself

	// DirectX related objects and variables
	D3D_FEATURE_LEVEL		dxFeatureLevel;
	IDXGISwapChain*			swapChain;
	ID3D11Device*			device;
	ID3D11DeviceContext*	context;

	ID3D11RenderTargetView* backBufferRTV;
	ID3D11DepthStencilView* depthStencilView;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShaderNormalMap;
	SimplePixelShader* pixelShaderNormalMap;
	SimpleVertexShader* skyVS;
	SimplePixelShader* skyPS;

	SimplePixelShader* pixelShaderBlend;
	SimplePixelShader* pixelShaderNormalMapBlend;

	MusicPlayer musicPlayer;

	Renderer Render;
};

