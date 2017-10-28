#include "Mesh.h"
#include "D3D11Mesh.h"


Mesh::Mesh() {

}

Mesh::Mesh(wchar_t* obj)
{

	objName = obj;

}


Mesh::~Mesh()
{
}

void Mesh::choosePlatform() {
	#if _PC
		//this = new D3D11Mesh(L"cube", device, false);
	#endif
	//
	#if _PS4
		// PS4 Resource Manager or Material Manager
	#endif
}