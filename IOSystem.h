#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;
class IOSystem
{
public:
	IOSystem();
	~IOSystem();

	virtual void loadObj(wchar_t* ) = 0;
	virtual void loadTexture2d(wchar_t*) = 0;
	virtual void loadCubemap(wchar_t*) = 0;


};

