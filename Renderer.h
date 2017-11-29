#pragma once

#include "SimpleShader.h"
#include "D3D11Material.h"
#include "Camera.h"
#include "Scene.h"
#include "GaussianBlur.h"
#include "Bloom.h"
#include "Animation.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(Camera*, ID3D11Device*, ID3D11DeviceContext*, ID3D11RenderTargetView*, IDXGISwapChain*, ID3D11DepthStencilView*, unsigned int width, unsigned int height);
	void Resized(ID3D11DepthStencilView*, ID3D11RenderTargetView*, unsigned int width, unsigned int height);
	void Draw();

	void Update(float t);

	void SetShaders(SimpleVertexShader*, SimplePixelShader*, SimpleVertexShader*, SimplePixelShader*,
		SimpleVertexShader*, SimplePixelShader*, SimplePixelShader*, SimplePixelShader*);

	void SetScene(Scene*);

private:
	void setWidthHeight(unsigned int width, unsigned int height, ID3D11DepthStencilView* depthStencilView);
	void SetPixelShaderUp(SimplePixelShader*, D3D11Material *material);
	void CreateAdditionalRSStates();

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShaderNormalMap;
	SimpleVertexShader* skinnedMeshVS;
	SimplePixelShader* pixelShaderNormalMap;
	SimpleVertexShader* skyVS;
	SimplePixelShader* skyPS;

	SimplePixelShader* pixelShaderBlend;
	SimplePixelShader* pixelShaderNormalMapBlend;

	// Particle Shaders
	SimpleVertexShader* particleVS;
	SimplePixelShader* particlePS;

	Camera* camera;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* context;
	ID3D11RenderTargetView* backBufferRTV;
	IDXGISwapChain* swapChain;
	ID3D11DepthStencilView* mDepthStencilView;

	ID3D11RenderTargetView* ppRTV;	
	ID3D11ShaderResourceView* ppSRV;

	GaussianBlur *blur;
	Bloom *bloom;

	Scene* currentScene;

	// Render states
	ID3D11RasterizerState* defaultState;
	ID3D11RasterizerState* rsNoCull;
	ID3D11BlendState* bsAlphaBlend;

	glm::mat4 mSkullWorld;
};