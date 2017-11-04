#pragma once
#include "Mesh.h"
#include <d3d11.h>

class D3D11Mesh : public Mesh
{

public:
	D3D11Mesh(char * path, ID3D11Device * device);
	~D3D11Mesh();

	void* GetVertexBuffer();
	void* GetIndexBuffer();

private:
	
	ID3D11Buffer* vertBuffer;
	ID3D11Buffer* indBuffer;
	uint16_t indCount;

	bool hasNormalMap;

	std::vector<Vertex> vertexCollection;
	std::vector<uint16_t> indexCollection;
	
	void CreateGeometry(Vertex*, uint16_t, uint16_t*, ID3D11Device*);
};
