#pragma once
#include "IOSystem.h"



class PC_IOSystem :
	public IOSystem
{
	
	vector<Vertex> verts;           // Verts we're assembling
	vector<size_t> indices;           // Indices of these verts
public:
	PC_IOSystem();
	~PC_IOSystem();

	void loadObj(wchar_t* ) override;
	vector<Vertex> getVertexFromObj();
	vector<size_t> getindixFromObj();

	void loadTexture2d(wchar_t*) override;
	void loadCubemap(wchar_t*) override;


};

