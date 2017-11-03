#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
//#include "WindowsRenderSystem.h"
//#include <d3d11.h>
//#include <DirectXMath.h>

class PC_IOSystem :
	public IOSystem
{
	static PC_IOSystem * IO_instance;
	//vector<Vertex> vertexCollection;
	////vector<size_t> indexCollection;
	//vector<UINT> indexCollection;

	//int indCount;

	
public:
	PC_IOSystem();
	~PC_IOSystem();

	//void loadObj(char* ) override;
	bool hasNormalMap;

	void loadTexture2d(wchar_t*) override;
	void loadCubemap(wchar_t*) override;

	static PC_IOSystem *instance()
	{
		if (!IO_instance)
			IO_instance = new PC_IOSystem;
		return IO_instance;
	}
};

