#pragma once
#include "Mesh.h"
#include <d3d11.h>

class D3D11Mesh : public Mesh
{

public:
	D3D11Mesh(char * path, ID3D11Device * device);
	~D3D11Mesh();

private:
	void CreateGeometry(ID3D11Device*);
};
