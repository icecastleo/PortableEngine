#pragma once
#include "Material.h"
#include "SimpleShader.h"
#include "Vertex.h"

class D3D11Material : public Material
{
public:
	D3D11Material(ID3D11Device * device, ID3D11DeviceContext * context, MaterialType type, const wchar_t * path, const wchar_t * normalpath);
	~D3D11Material();

	void SetTexture(ID3D11Device * device, ID3D11DeviceContext * context, const wchar_t * path, const wchar_t * normalpath);
	void SetupSkybox(ID3D11Device * device, ID3D11DeviceContext * context, const wchar_t * path);
	
	void PrepareMaterial(glm::mat4 world, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> &boneTransforms, SimpleVertexShader * vertexShader, SimplePixelShader * pixelShader);

	ID3D11ShaderResourceView* GetSRV();

	ID3D11SamplerState* GetSampleState();

	ID3D11RasterizerState* GetRast();
	ID3D11DepthStencilState* GetDepthSD();
private:

	ID3D11ShaderResourceView* SRV;

	ID3D11SamplerState* sampleState;

	ID3D11RasterizerState* rsSky;
	ID3D11DepthStencilState* dsSky;
};