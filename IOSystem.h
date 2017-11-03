#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;
class IOSystem
{
	//static IOSystem * IO_instance;

protected:
	vector<Vertex> vertexCollection;
	vector<uint16_t> indexCollection;

	uint16_t indCount;

public:
	IOSystem();
	virtual ~IOSystem();

	void loadObj(char* );
	virtual void loadTexture2d(wchar_t*) = 0;
	virtual void loadCubemap(wchar_t*) = 0;

	//static IOSystem *instance();

	virtual vector<Vertex> getVertexFromObj();
	////vector<size_t> getindixFromObj();
	virtual vector<uint16_t> getIndicesFromObj();
	virtual uint16_t getIndCount();
};

