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
}

Mesh* PC_IOSystem::loadMesh(wchar_t *objName)
{
	wstring path = L"Assets/Models/" + (wstring)objName + L".obj";
	const wchar_t *src = path.c_str();
	size_t size = wcslen(path.c_str()) * 2 + 2;
	char *cPath = new char[size];
	size_t result;

	// success
	if (wcstombs_s(&result, cPath, size, src, size) != 0) {
		perror("Failed to convert wstring to c string \n");
		return nullptr;
	}

	Mesh *ret = new D3D11Mesh(cPath, device);

	delete cPath;

	return ret;
}

Material* PC_IOSystem::loadTexture2d(const wchar_t* texturepath) {
	

	Material * ret = new D3D11Material(device, context, texturepath);
	
	return ret;

}

Material* PC_IOSystem::loadTexture2d(const wchar_t* texturepath, const wchar_t* normalpath) {


	Material * ret = new D3D11Material(device, context, texturepath, normalpath);
	

	return ret;

}

Material* PC_IOSystem::loadTexture2d(const wchar_t* texturepath, int type) {


	Material * ret = new D3D11Material(device, context, texturepath, type);

	return ret;

}



