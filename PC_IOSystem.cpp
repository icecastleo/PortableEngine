
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

//Mesh* PC_IOSystem::loadMesh(wchar_t *objName)
//{
//	wstring path = L"Assets/Models/" + (wstring)objName + L".obj";
//	const wchar_t *src = path.c_str();
//	size_t size = wcslen(path.c_str()) * 2 + 2;
//	char *cPath = new char[size];
//	size_t result;
//
//	// success
//	if (wcstombs_s(&result, cPath, size, src, size) != 0) {
//		perror("Failed to convert wstring to c string \n");
//		return nullptr;
//	}
//
//	Mesh *ret = new D3D11Mesh(cPath, device);
//
//	delete cPath;
//
//	return ret;
//}

Material* PC_IOSystem::loadTexture2d(const wchar_t* textureName, const wchar_t* normalmapName = nullptr) {
	
	wstring path = L"Assets/textures/" + (wstring)textureName + L".png";
	const wchar_t *src = path.c_str();

	const wchar_t *normalSrc = nullptr;

	if (normalmapName) {
		wstring pathN = L"Assets/textures/" + (wstring)normalmapName + L".png";
		normalSrc = pathN.c_str();
	}

	return new D3D11Material(device, context, kMaterialNormal, src, normalSrc);
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
		shaderNames.push_back(shaderName);
}

void PC_IOSystem::loadPSShader(const wchar_t * shaderName) {
		wstring path = L"Assets/ShaderObjs/" + (wstring)shaderName + L".cso";
		LPCWSTR cPath = path.c_str();
		SimplePixelShader* ret = new SimplePixelShader(device, context);
		if (!ret->LoadShaderFile(cPath))
			ret->LoadShaderFile(((wstring)shaderName + L".cso").c_str());

		PSmap.insert(std::pair<const wchar_t *, SimplePixelShader*>(shaderName, ret));
		shaderNames.push_back(shaderName);
}

SimpleVertexShader* PC_IOSystem::getVertexShader(const wchar_t * vsName) {
	return VSmap.at(vsName);
}

SimplePixelShader* PC_IOSystem::getPixelShader(const wchar_t * psName) {
	
	return PSmap.at(psName);
}