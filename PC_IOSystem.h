#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
#include <d3d11.h>


class PC_IOSystem :
	public IOSystem
{

public:
	PC_IOSystem(ID3D11Device *device, ID3D11DeviceContext* context);
	~PC_IOSystem();

	Mesh* loadMesh(wchar_t *) override;
	Material* loadTexture2d(const wchar_t*) override;
	Material* loadTexture2d(const wchar_t*, const wchar_t*) override;
	Material* loadTexture2d(const wchar_t*, int) override;
	

private:
	ID3D11Device *device;
	ID3D11DeviceContext* context;
};

