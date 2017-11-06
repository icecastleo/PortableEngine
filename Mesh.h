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

	std::vector<Vertex> GetVertices();
	std::vector<uint16_t> GetIndices();

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

