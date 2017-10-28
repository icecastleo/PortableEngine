#pragma once
#include "Vertex.h"
#include <vector>
#include "DXCore.h"

using namespace std;
class IOSystem
{
	/*static IOSystem * IO_instance;


	vector<Vertex> vertexCollection;
	vector<UINT> indexCollection;

	int indCount;*/



public:
	IOSystem();
	~IOSystem();

	virtual void loadObj(wchar_t* ) = 0;
	virtual void loadTexture2d(wchar_t*) = 0;
	virtual void loadCubemap(wchar_t*) = 0;

	//static IOSystem *instance();

	//virtual vector<Vertex> getVertexFromObj() = 0;
	//////vector<size_t> getindixFromObj();
	//virtual vector<UINT> getindixFromObj() = 0;
	//virtual int getindCount() = 0;

};

