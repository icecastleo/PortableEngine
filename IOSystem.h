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

	vector<const wchar_t *> shaderNames;

public:
	IOSystem();
	virtual ~IOSystem();

	virtual Mesh* loadMesh(wchar_t* objName) = 0;

	virtual Material* loadTexture2d(const wchar_t* textureName, const wchar_t* normalmapName = nullptr) = 0;
	virtual Material* loadCubemapTexture(const wchar_t* texturename) = 0;
	
	virtual void loadVSShader(const wchar_t *) = 0;
	virtual void loadPSShader(const wchar_t *) = 0;

	bool isinMap(const wchar_t *);  //check if the shader is loaded
};

