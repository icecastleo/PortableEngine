 #include "D3D11Material.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

D3D11Material::D3D11Material(ID3D11Device* device, ID3D11DeviceContext* context, MaterialType type, const wchar_t* path, const wchar_t* normalpath = nullptr)
{
	sampleState = nullptr;
	SRV = nullptr;
	normalSRV = nullptr;

	this->type = type;

	if (type == kMaterialNormal) {
		SetTexture(device, context, path, normalpath);
	}
	else if (type == kMaterialCubemap) {
		SetupSkybox(device, context, path);
	}
}

D3D11Material::~D3D11Material() 
{
	if (SRV)
		SRV->Release();

	if (normalSRV)
		static_cast<ID3D11ShaderResourceView*>(normalSRV)->Release();

	if (rsSky)
		rsSky->Release();

	if (dsSky)
		dsSky->Release();

	sampleState->Release();
}

//---------------------------------------------------------
//Set the material's texture
//---------------------------------------------------------
void D3D11Material::SetTexture(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path, const wchar_t* normalpath = nullptr)
{
	D3D11_SAMPLER_DESC sampleDes = {};
	sampleDes.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDes.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&sampleDes, &sampleState);

	DirectX::CreateWICTextureFromFile(device, context, path, 0, &SRV);

	if (normalpath) {
		DirectX::CreateWICTextureFromFile(device, context, normalpath, 0, reinterpret_cast<ID3D11ShaderResourceView**>(&normalSRV));
	}
}

void D3D11Material::SetupSkybox(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path)
{
	D3D11_SAMPLER_DESC sampleDes = {};
	sampleDes.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDes.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&sampleDes, &sampleState);

	HRESULT hr;
	hr = DirectX::CreateDDSTextureFromFile(device, path, 0, &SRV);

	if (FAILED(hr)) return;

	D3D11_RASTERIZER_DESC rsDesc = {};
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_FRONT;
	rsDesc.DepthClipEnable = true;
	device->CreateRasterizerState(&rsDesc, &rsSky);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	device->CreateDepthStencilState(&dsDesc, &dsSky);
}

//---------------------------------------------------------
//Prepare the material for drawing
//---------------------------------------------------------
void D3D11Material::PrepareMaterial(glm::mat4 world, glm::mat4 view, glm::mat4 projection, SimpleVertexShader* vertexShader, SimplePixelShader* pixelShader)
{
	if (type == kMaterialNormal) {
		// Send data to shader variables
		//  - Do this ONCE PER OBJECT you're drawing
		//  - This is actually a complex process of copying data to a local buffer
		//    and then copying that entire buffer to the GPU.  
		//  - The "SimpleShader" class handles all of that for you.
		vertexShader->SetMatrix4x4("world", world);
		vertexShader->SetMatrix4x4("view", view);
		vertexShader->SetMatrix4x4("projection", projection);

		// Once you've set all of the data you care to change for
		// the next draw call, you need to actually send it to the GPU
		//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
		vertexShader->CopyAllBufferData();

		// Set the vertex and pixel shaders to use for the next Draw() command
		//  - These don't technically need to be set every frame...YET
		//  - Once you start applying different shaders to different objects,
		//    you'll need to swap the current shaders before each draw
		vertexShader->SetShader();
	}
	else if (type == kMaterialCubemap) {
		vertexShader->SetMatrix4x4("view", view);
		vertexShader->SetMatrix4x4("projection", projection);
		vertexShader->CopyAllBufferData();
		vertexShader->SetShader();

		// TODO: Move to pixel shader up
		pixelShader->SetShaderResourceView("Sky", SRV);
		pixelShader->CopyAllBufferData();
		pixelShader->SetShader();
	}
}

ID3D11ShaderResourceView* D3D11Material::GetSRV()
{
	return SRV;
}

ID3D11SamplerState* D3D11Material:: GetSampleState()
{
	return sampleState;
}

ID3D11RasterizerState* D3D11Material::GetRast()
{
	return rsSky;
}

ID3D11DepthStencilState* D3D11Material::GetDepthSD()
{
	return dsSky;
}