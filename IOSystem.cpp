#include "IOSystem.h"
#include <cstdint>
#include <string>

IOSystem::IOSystem()
{
}


IOSystem::~IOSystem()
{
}

bool IOSystem::isinMap(const wchar_t * shadeName) {
	if (std::find(shaderNames.begin(), shaderNames.end(), shadeName) != shaderNames.end()) {
		return true;
	}
	else {
		return false;
	}
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
