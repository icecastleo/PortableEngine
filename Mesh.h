#pragma once
#include "DXCore.h"
#include <d3d11.h>
#include <DirectXMath.h>    //will change
#include "Vertex.h"
#include "IOSystem.h"
#include <fstream>
#include <vector>

class Mesh
{
	
	wchar_t* objName;
public:
	Mesh();
	Mesh(wchar_t* );
	~Mesh();

	void choosePlatform();
};

