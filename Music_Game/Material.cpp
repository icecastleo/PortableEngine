//Darren Farr
#include "Material.h"

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Material::Material() {}

//---------------------------------------------------------
//Constructor override to create a material from a texture path
//---------------------------------------------------------
Material::Material(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path)
{
	SetTexture(device, context, path);
}

//---------------------------------------------------------
//Constructor override to create a material for a skybox
//---------------------------------------------------------
Material::Material(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path, bool isSkybox)
{
	if(isSkybox)
		SetupSkybox(device, context, path);
	else
		SetupParticle(device, context, path);
}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
Material::~Material() 
{
	if (SRV != nullptr) { SRV->Release(); }
	sampleState->Release();
	if (skySRV != nullptr)
	{
		skySRV->Release();
		rsSky->Release();
		dsSky->Release();
	}
	delete sampleDes;
	
	if(particleTexture!= nullptr)
		particleTexture->Release();
	
	particleBlendState->Release();
	particleDepthState->Release();

}

//---------------------------------------------------------
//Set the material's texture
//---------------------------------------------------------
void Material::SetTexture(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path)
{
	sampleState = nullptr;
	sampleDes = new D3D11_SAMPLER_DESC();
	sampleDes->AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDes->MaxLOD = D3D11_FLOAT32_MAX;

	SRV = nullptr;
	skySRV = nullptr;

	DirectX::CreateWICTextureFromFile(device, context, path, 0, &SRV);

	device->CreateSamplerState(sampleDes, &sampleState);
}

//---------------------------------------------------------
//Set the material's texture
//---------------------------------------------------------
void Material::SetupSkybox(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path)
{

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

	sampleState = nullptr;
	sampleDes = new D3D11_SAMPLER_DESC();
	sampleDes->AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDes->Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDes->MaxLOD = D3D11_FLOAT32_MAX;

	SRV = nullptr;
	skySRV = nullptr;

	HRESULT hr;
	hr = DirectX::CreateDDSTextureFromFile(device, path, 0, &skySRV);

	device->CreateSamplerState(sampleDes, &sampleState);
}

void Material::SetupParticle(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* path)
{
	DirectX::CreateWICTextureFromFile(device, context, path, 0, &particleTexture);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // Turns off depth writing
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	device->CreateDepthStencilState(&dsDesc, &particleDepthState);

	// Blend for particles (additive)
	D3D11_BLEND_DESC blend = {};
	blend.AlphaToCoverageEnable = false;
	blend.IndependentBlendEnable = false;
	blend.RenderTarget[0].BlendEnable = true;
	blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blend.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blend, &particleBlendState);
}

//---------------------------------------------------------
//Prepare the material for drawing
//---------------------------------------------------------
void Material::PrepareMaterial(DirectX::XMFLOAT4X4 world, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection, SimpleVertexShader* vertexShader)
{
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

void Material::PrepareSkybox(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection, SimpleVertexShader* skyVS, SimplePixelShader* skyPS)
{
	skyVS->SetMatrix4x4("view", view);
	skyVS->SetMatrix4x4("projection", projection);
	skyVS->CopyAllBufferData();
	skyVS->SetShader();

	skyPS->SetShaderResourceView("Sky", skySRV);
	skyPS->CopyAllBufferData();
	skyPS->SetShader();
}

//---------------------------------------------------------
//Return the SRV
//---------------------------------------------------------
ID3D11ShaderResourceView* Material::GetSRV()
{
	return SRV;
}

//---------------------------------------------------------
//Return the skybox SRV
//---------------------------------------------------------
ID3D11ShaderResourceView* Material::GetSkySRV()
{
	return skySRV;
}

//---------------------------------------------------------
//Return the Sample State
//---------------------------------------------------------
ID3D11SamplerState* Material:: GetSampleState()
{
	return sampleState;
}

//---------------------------------------------------------
//Return the Rasterrizer Desc
//---------------------------------------------------------
ID3D11RasterizerState* Material::GetRast()
{
	return rsSky;
}

//---------------------------------------------------------
//Return the Rasterrizer Desc
//---------------------------------------------------------
ID3D11DepthStencilState* Material::GetDepthSD()
{
	return dsSky;
}

ID3D11DepthStencilState* Material::GetParticleDepthState()
{
	return particleDepthState;
}

ID3D11BlendState* Material::GetParticleBlendState()
{
	return particleBlendState;
}

ID3D11ShaderResourceView* Material::GetParticleTexture()
{
	return particleTexture;
}