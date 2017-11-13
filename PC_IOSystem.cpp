
#include "PC_IOSystem.h"
#include "D3D11Mesh.h"
#include "D3D11Material.h"

//PC_IOSystem *PC_IOSystem::IO_instance = 0;

PC_IOSystem::PC_IOSystem(ID3D11Device *device, ID3D11DeviceContext* context)
	:device(device),context(context)
{

}

PC_IOSystem::~PC_IOSystem()
{
	for (auto it = VSmap.cbegin(); it != VSmap.cend(); ++it)
	{
		delete VSmap.at(it->first);
	}
	for (auto it = PSmap.cbegin(); it != PSmap.cend(); ++it)
	{
		delete PSmap.at(it->first);
	}
}

wstring PC_IOSystem::getMeshPath(const wchar_t * name)
{
	return L"Assets/Models/" + (wstring)name + L".obj";
}

Mesh * PC_IOSystem::loadMesh(char * cPath)
{
	return new D3D11Mesh(cPath, device);
}

wstring PC_IOSystem::getTexturePath(const wchar_t * name)
{
	return L"Assets/textures/" + (wstring)name + L".png";
}

Material * PC_IOSystem::loadTexture2DFromPath(const wchar_t* texturePath, const wchar_t* normalmapPath = nullptr)
{
	return new D3D11Material(device, context, kMaterialNormal, texturePath, normalmapPath);
}

Material* PC_IOSystem::loadCubemapTexture(const wchar_t* texturename) {
	wstring path = L"Assets/textures/" + (wstring)texturename + L".dds";
	const wchar_t *src = path.c_str();

	return new D3D11Material(device, context, kMaterialCubemap, src, nullptr);
}

void PC_IOSystem::loadVSShader(const wchar_t * shaderName) {
		wstring path = L"Assets/ShaderObjs/" + (wstring)shaderName + L".cso";
		LPCWSTR cPath = path.c_str();
		SimpleVertexShader* ret = new SimpleVertexShader(device, context);
		if (!ret->LoadShaderFile(cPath))
			ret->LoadShaderFile(((wstring)shaderName + L".cso").c_str());

		VSmap.insert(std::pair<const wchar_t *, SimpleVertexShader*>(shaderName, ret));
		
}

void PC_IOSystem::loadPSShader(const wchar_t * shaderName) {
		wstring path = L"Assets/ShaderObjs/" + (wstring)shaderName + L".cso";
		LPCWSTR cPath = path.c_str();
		SimplePixelShader* ret = new SimplePixelShader(device, context);
		if (!ret->LoadShaderFile(cPath))
			ret->LoadShaderFile(((wstring)shaderName + L".cso").c_str());

		PSmap.insert(std::pair<const wchar_t *, SimplePixelShader*>(shaderName, ret));
		
}

SimpleVertexShader* PC_IOSystem::getVertexShader(const wchar_t * vsName) {
	return VSmap.at(vsName);
}

SimplePixelShader* PC_IOSystem::getPixelShader(const wchar_t * psName) {
	
	return PSmap.at(psName);
}