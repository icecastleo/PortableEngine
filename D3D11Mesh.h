//Darren Farr GGP
#pragma once
#include "Mesh.h"


class D3D11Mesh : public Mesh
{

public:
	D3D11Mesh();
	D3D11Mesh(wchar_t* objName,  ID3D11Device*, bool);
	~D3D11Mesh();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();

	std::vector<Vertex> GetVertexCollection();
	//std::vector<size_t> GetIndexCollection();
	std::vector<UINT> GetIndexCollection();

	void CalculateTangents(Vertex*, int, unsigned int*, int);

private:
	

	ID3D11Buffer* vertBuffer;
	ID3D11Buffer* indBuffer;
	int indCount;

	bool hasNormalMap;

	std::vector<Vertex> vertexCollection;
	//std::vector<size_t> indexCollection;
	std::vector<UINT> indexCollection;
	

	//void CreateGeometry(Vertex*, int, size_t *, ID3D11Device*);
	void CreateGeometry(Vertex*, int, unsigned int *, ID3D11Device*);

	
};
