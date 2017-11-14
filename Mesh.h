#pragma once

#include "Vertex.h"
#include <vector>

class Mesh
{
public:
	Mesh(char *path);
	~Mesh();

	std::vector<Vertex> GetVertices();
	std::vector<uint16_t> GetIndices();

	void* GetVertexBuffer();
	void* GetIndexBuffer();

protected:
	void* vertBuffer;
	void* indBuffer;

	bool hasNormalMap;

	std::vector<Vertex> verts;
	std::vector<uint16_t> indices;

private:
	void loadVertices(char *path);
	void CalculateTangents(Vertex*, uint16_t, uint16_t*, uint16_t);
};

