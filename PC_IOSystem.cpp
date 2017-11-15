
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
		delete it->first;
		delete static_cast<SimpleVertexShader*> (it->second);
	}
	for (auto it = PSmap.cbegin(); it != PSmap.cend(); ++it)
	{
		delete it->first;
		delete static_cast<SimpleVertexShader*>(it->second);
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

wstring PC_IOSystem::getShaderPath(const wchar_t *name)
{
	return L"Assets/ShaderObjs/" + (wstring)name + L".cso";
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

void* PC_IOSystem::loadVSShaderFromPath(const wchar_t * shaderPath) {
		
	    SimpleVertexShader * ret = new SimpleVertexShader(device, context);
		//if (!ret->LoadShaderFile(shaderPath))
			ret->LoadShaderFile(shaderPath);
		return ret;
}

void* PC_IOSystem::loadPSShaderFromPath(const wchar_t * shaderPath) {
		
		SimplePixelShader* ret = new SimplePixelShader(device, context);
		//if (!ret->LoadShaderFile(shaderPath))
			ret->LoadShaderFile(shaderPath);

		return ret;
}

