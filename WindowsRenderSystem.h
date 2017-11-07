//Original code - Chris Cascioli
//Modified for use in homework
#pragma once

#include "RenderSystem.h"
#include "D3D11.h"
#include "SimpleShader.h"
//#include <DirectXMath.h>
#include "SceneManager.h"
#include "SceneBuilder.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"
#include "Asteroid.h"
#include "MusicPlayer.h"
#include <vector>
#include "Tex2Dt.h"

// We can include the correct library files here
// instead of in Visual Studio settings if we want
#pragma comment(lib, "d3d11.lib")


class WindowsRenderSystem
	: public RenderSystem
{

public:
	WindowsRenderSystem(uint16_t width, uint16_t height, HWND hWnd);
	~WindowsRenderSystem();

	void OnResize(uint16_t width, uint16_t height) override;
	void Update(float deltaTime) override;
	void Draw() override;

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void SetScene(Scene *scene);
	
private:

	void Init(uint16_t width, uint16_t height);
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

	Scene *scene;

	Renderer Render;

	Asteroid* curAsteroid;
	int curIndex = 0;
	float timer = 0.2f;
	int asteroidIndex = 0;
	float stayTime = 0;
	float sceneChangeTime = 0;

	Text2D* text;
};

