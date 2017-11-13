#pragma once
#include "IOSystem.h"
#include "Vertex.h"
#include <fstream>
#include <d3d11.h>
#include <map>
#include "SimpleShader.h"


class PC_IOSystem :
	public IOSystem
{

public:
	PC_IOSystem(ID3D11Device *device, ID3D11DeviceContext* context);
	~PC_IOSystem();

	Mesh* loadMesh(wchar_t *) override;

	Material* loadTexture2d(const wchar_t*, const wchar_t*) override;
	Material * loadCubemapTexture(const wchar_t * texturename) override;

	void loadVSShader(const wchar_t *);
	void loadPSShader(const wchar_t *);
   
	SimpleVertexShader* getVertexShader(const wchar_t *);
	SimplePixelShader* getPixelShader(const wchar_t *);
   
private:
	ID3D11Device *device;
	ID3D11DeviceContext* context;
    
	std::map<const wchar_t *, SimpleVertexShader*> VSmap;
	std::map<const wchar_t *, SimplePixelShader*> PSmap;
};

