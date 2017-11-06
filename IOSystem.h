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
	virtual Material* loadTexture2d(const wchar_t*, const wchar_t*) = 0; //for normalmap
	virtual Material* loadTexture2d(const wchar_t*, int) = 0; //for cubemap or particle
	
	virtual void loadVSShader(const wchar_t *) = 0;
	virtual void loadPSShader(const wchar_t *) = 0;


};

