#pragma once

#include "Vertex.h"
#include <vector>

class Mesh
{
public:
	Mesh(char *path);
	~Mesh();

	virtual void* GetVertexBuffer() = 0;
	virtual void* GetIndexBuffer() = 0;
	uint16_t GetIndexCount();

	std::vector<Vertex> GetVertexCollection();
	std::vector<uint16_t> GetIndexCollection();

	void CalculateTangents(Vertex*, uint16_t, uint16_t*, uint16_t);

private:
	void loadVertices(char *path);

	void* vertBuffer;
	void* indBuffer;
	uint16_t indCount;

	bool hasNormalMap;

	std::vector<Vertex> vertexCollection;
	std::vector<uint16_t> indexCollection;
};

