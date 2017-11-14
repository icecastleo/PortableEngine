#include "IOSystem.h"
#include <cstdint>
#include <string>

IOSystem::IOSystem()
{
}


IOSystem::~IOSystem()
{
}

Mesh * IOSystem::loadMesh(wchar_t * name)
{
	wstring path = getMeshPath(name);
	const wchar_t *src = path.c_str();
	size_t size = wcslen(path.c_str()) * 2 + 2;
	char *cPath = new char[size];
	size_t result;

	// success
	assert(wcstombs_s(&result, cPath, size, src, size) == 0);

	Mesh *ret = loadMesh(cPath);

	delete cPath;

	return ret;
}

Material * IOSystem::loadTexture2D(const wchar_t * textureName, const wchar_t * normalmapName)
{
	wstring path = getTexturePath(textureName);
	const wchar_t *texturePath = path.c_str();

	const wchar_t *normalTexturePath = nullptr;
	wstring pathN;

	if (normalmapName) {
		pathN = getTexturePath(normalmapName);
		normalTexturePath = pathN.c_str();
	}
	
	return loadTexture2DFromPath(texturePath, normalTexturePath);
}

void* IOSystem::loadVSShader(const wchar_t * shaderName) {
	wstring path = getShaderPath(shaderName);
	const wchar_t *shaderPath = path.c_str();

	wstring name = (wstring) shaderName;
	const wchar_t *src = name.c_str();
	size_t size = wcslen(name.c_str()) * 2 + 2;
	char *cPath = new char[size];
	size_t result;

	// success
	assert(wcstombs_s(&result, cPath, size, src, size) == 0);

	if (VSmap.count(cPath) == 0) {
		void * ret = loadVSShaderFromPath(shaderPath, cPath);
		VSmap.insert(std::pair<char*, void*>(cPath, ret));
	}

	return VSmap.at(cPath);
}

void* IOSystem::loadPSShader(const wchar_t * shaderName) {
	wstring path = getShaderPath(shaderName);
	const wchar_t *shaderPath = path.c_str();

	wstring name = (wstring)shaderName;
	const wchar_t *src = name.c_str();
	size_t size = wcslen(name.c_str()) * 2 + 2;
	char *cPath = new char[size];
	size_t result;

	// success
	assert(wcstombs_s(&result, cPath, size, src, size) == 0);

	void * ret;
	if (PSmap.count(cPath) == 0) {   //check the shader if in the map
		void * ret = loadPSShaderFromPath(shaderPath, cPath);
		PSmap.insert(std::pair<char*, void*>(cPath, ret));
	}
	
	return PSmap.at(cPath);
}


// FIXME: Duplicated code




//Mesh * IOSystem::loadMesh(wchar_t * objName)
//{
//	wstring path = L"Assets/Models/" + (wstring)objName + L".obj";
//	const wchar_t *src = path.c_str();
//	size_t size = wcslen(path.c_str()) * 2 + 2;
//	char *cPath = new char[size];
//	size_t ret;
//
//	// success
//	assert(wcstombs_s(&ret, cPath, size, src, size) == 0);
//
//
//	delete cPath;
//
//#if defined(_PC)  
//
//
//#elif defined(_PS4)  
//
//#else  
//	return nullptr;
//#endif
//}
