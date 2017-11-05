#include "PC_IOSystem.h"
#include "D3D11Mesh.h"

//PC_IOSystem *PC_IOSystem::IO_instance = 0;

PC_IOSystem::PC_IOSystem(ID3D11Device *device)
	:device(device)
{

}


PC_IOSystem::~PC_IOSystem()
{
}

Mesh* PC_IOSystem::loadMesh(wchar_t *objName)
{
	wstring path = L"Assets/Models/" + (wstring)objName + L".obj";
	const wchar_t *src = path.c_str();
	size_t size = wcslen(path.c_str()) * 2 + 2;
	char *cPath = new char[size];
	size_t result;

	// success
	assert(wcstombs_s(&result, cPath, size, src, size) == 0);

	Mesh *ret = new D3D11Mesh(cPath, device);

	delete cPath;

	return ret;
}

void PC_IOSystem::loadTexture2d(wchar_t*) {

}
void PC_IOSystem::loadCubemap(wchar_t*) {

}
