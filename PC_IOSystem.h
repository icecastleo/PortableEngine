#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
//#include "WindowsRenderSystem.h"
//#include <d3d11.h>


class PC_IOSystem :
	public IOSystem
{
	//static PC_IOSystem * IO_instance;

public:
	PC_IOSystem(ID3D11Device *device);
	~PC_IOSystem();

	Mesh* loadMesh(wchar_t *) override;
	void loadTexture2d(wchar_t*) override;
	void loadCubemap(wchar_t*) override;

	//static PC_IOSystem *instance()
	//{
	//	if (!IO_instance)
	//		IO_instance = new PC_IOSystem;
	//	return IO_instance;
	//}

private:
	ID3D11Device *device;
};

