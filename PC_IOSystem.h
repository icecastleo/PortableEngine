#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
#include <d3d11.h>


class PC_IOSystem :
	public IOSystem
{

public:
	PC_IOSystem(ID3D11Device *device);
	~PC_IOSystem();

	Mesh* loadMesh(wchar_t *) override;
	void loadTexture2d(wchar_t*) override;
	void loadCubemap(wchar_t*) override;

private:
	ID3D11Device *device;
};

