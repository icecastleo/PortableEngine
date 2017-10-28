//Original code - Chris Cascioli
//Modified for use in homework
#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "SceneManager.h"
#include "SceneBuilder.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"
#include "Asteroid.h"
#include "Collision.h"
#include "MusicPlayer.h"
#include <vector>
#include "Tex2Dt.h"

class Game
	: public RenderSystem
{

public:
	Game(unsigned int windowWidth, unsigned int windowHeight, HWND hWnd);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime);
	void Draw();

	HRESULT InitDirectX();
	
private:
	HWND		hWnd;			// The handle to the window itself

	unsigned int width;			// Size of the window's client area
	unsigned int height;

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

	int SceneNumber;

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders();
	void setScene();

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShaderNormalMap;
	SimplePixelShader* pixelShaderNormalMap;
	SimpleVertexShader* skyVS;
	SimplePixelShader* skyPS;

	SimplePixelShader* pixelShaderBlend;
	SimplePixelShader* pixelShaderNormalMapBlend;

	// Particle Shaders
	SimpleVertexShader* particleVS;
	SimplePixelShader* particlePS;

	MusicPlayer musicPlayer;

	Scene* menueScene;
	Scene* gameScene;
	Scene* endScene;

	SceneBuilder SceneBuild;
	SceneManager SceneManag;
	Renderer Render;
	Camera Cam;

	Player *player;
	void SetNextAsteroid();
	std::vector<Asteroid*> asteroids;
	Asteroid* curAsteroid;
	int curIndex = 0;
	float timer = 0.2f;
	int asteroidIndex = 0;
	float stayTime = 0;
	float sceneChangeTime = 0;

	int score;

	Text2D* text;
};

