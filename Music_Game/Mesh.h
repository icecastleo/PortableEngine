//Darren Farr GGP
#pragma once

#include "DXCore.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vertex.h"
#include <fstream>
#include <vector>

class Mesh
{

public:
	Mesh();
	Mesh(char*, ID3D11Device*);
	Mesh(Vertex*, int, UINT*, int, ID3D11Device*);
	~Mesh();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	unsigned int GetIndexCount();

private:
	ID3D11Buffer* vertBuffer;
	ID3D11Buffer* indBuffer;
	unsigned int indCount;

	void CreateGeometry(Vertex*, int, UINT*, ID3D11Device*);
};
