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

	//vector<const wchar_t *> shaderNames;

	virtual wstring getMeshPath(const wchar_t* name) = 0;
	virtual wstring getTexturePath(const wchar_t *name) = 0;
	virtual wstring getShaderPath(const wchar_t *name) = 0;

	std::map<char *, void*> VSmap;
	std::map<char *, void*> PSmap;
public:
	IOSystem();
	virtual ~IOSystem();

	Mesh* loadMesh(wchar_t* name);
	virtual Mesh * loadMesh(char *cPath) = 0;

	Material* loadTexture2D(const wchar_t* textureName, const wchar_t* normalmapName = nullptr);
	virtual Material* loadTexture2DFromPath(const wchar_t * texturePath, const wchar_t * normalmapPath) = 0;

	virtual Material* loadCubemapTexture(const wchar_t* texturename) = 0;
	
	virtual void loadVSShader(const wchar_t *) = 0;
	virtual void loadPSShader(const wchar_t *) = 0;

};

