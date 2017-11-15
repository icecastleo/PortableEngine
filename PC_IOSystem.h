#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
#include <d3d11.h>

#include "SimpleShader.h"


class PC_IOSystem :
	public IOSystem
{

protected:
	wstring getMeshPath(const wchar_t* name) override;
	wstring getTexturePath(const wchar_t * name) override;
	wstring getShaderPath(const wchar_t *name) override;

public:
	PC_IOSystem(ID3D11Device *device, ID3D11DeviceContext* context);
	~PC_IOSystem();

	Mesh* loadMesh(char *cPath) override;
	Material* loadTexture2DFromPath(const wchar_t * texturePath, const wchar_t * normalmapPath) override;
	Material* loadCubemapTexture(const wchar_t * texturename) override;

	void* loadVSShaderFromPath(const wchar_t *) override;
	void* loadPSShaderFromPath(const wchar_t *) override;
   
	
   
private:
	ID3D11Device *device;
	ID3D11DeviceContext* context;
    
	/*std::map<const wchar_t *, SimpleVertexShader*> VSmap;
	std::map<const wchar_t *, SimplePixelShader*> PSmap;*/
};

