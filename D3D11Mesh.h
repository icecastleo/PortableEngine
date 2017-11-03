#pragma once
#include "Mesh.h"

class D3D11Mesh : public Mesh
{

public:
	D3D11Mesh(wchar_t* objName,  ID3D11Device*, bool);
	~D3D11Mesh();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	size_t GetIndexCount();

	std::vector<Vertex> GetVertexCollection();
	std::vector<uint16_t> GetIndexCollection();

	void CalculateTangents(Vertex*, uint16_t, uint16_t*, uint16_t);

private:
	
	ID3D11Buffer* vertBuffer;
	ID3D11Buffer* indBuffer;
	uint16_t indCount;

	bool hasNormalMap;

	std::vector<Vertex> vertexCollection;
	std::vector<uint16_t> indexCollection;
	
	void CreateGeometry(Vertex*, uint16_t, uint16_t*, ID3D11Device*);
};
