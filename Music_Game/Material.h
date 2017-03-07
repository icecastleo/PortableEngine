//Darren Farr
#pragma once

#include <DirectXMath.h>
#include "SimpleShader.h"
#include "WICTextureLoader.h"


class Material
{
public:
	Material();
	Material(ID3D11Device*, ID3D11DeviceContext*, const wchar_t*);
	~Material();

	void PrepareMaterial(DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4, SimpleVertexShader*);
	void SetTexture(ID3D11Device*, ID3D11DeviceContext*, const wchar_t*);

	ID3D11ShaderResourceView* GetSRV();
	ID3D11SamplerState* GetSampleState();

private:
	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* sampleState;
	D3D11_SAMPLER_DESC* sampleDes;
};