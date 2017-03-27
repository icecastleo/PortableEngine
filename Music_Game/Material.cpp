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
//Default Deconstructor
//---------------------------------------------------------
Material::~Material() 
{
	SRV->Release();
	sampleState->Release();
	delete sampleDes;
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

	DirectX::CreateWICTextureFromFile(device, context, path, 0, &SRV);

	device->CreateSamplerState(sampleDes, &sampleState);
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

//---------------------------------------------------------
//Return the SRV
//---------------------------------------------------------
ID3D11ShaderResourceView* Material::GetSRV()
{
	return SRV;
}

//---------------------------------------------------------
//Return the Sample State
//---------------------------------------------------------
ID3D11SamplerState* Material:: GetSampleState()
{
	return sampleState;
}