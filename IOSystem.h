#pragma once
#include "Vertex.h"
#include <vector>
#include "Mesh.h"
#include "Material.h"

using namespace std;
class IOSystem
{
	
protected:
	vector<Vertex> vertexCollection;
	vector<uint16_t> indexCollection;

	uint16_t indCount;

public:
	IOSystem();
	virtual ~IOSystem();

	virtual Mesh* loadMesh(wchar_t* objName) = 0;
	virtual Material* loadTexture2d(const wchar_t*) = 0;
	virtual Material* loadTexture2d(const wchar_t*, int) = 0;
	
	virtual void loadCubemap(wchar_t*) = 0;

	//static IOSystem *instance();
};

