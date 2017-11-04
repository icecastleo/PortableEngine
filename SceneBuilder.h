//Darren Farr
#pragma once
#include "SimpleShader.h"
#include "Entity.h"
//#include <DirectXMath.h>
#include "D3D11Mesh.h"
#include "D3D11Material.h"
#include <vector>
#include "Lights.h"
#include "Scene.h"

//---------------------------------------------------------
//Scene Manager class
//Contains one or more scenes made up of entities, made of meshes and materials
//---------------------------------------------------------
class SceneBuilder
{
public:
	SceneBuilder();
	~SceneBuilder();

	void Init(ID3D11Device*, ID3D11DeviceContext*);
	void BuildMaterials();
	void BuildLights();
	void BuildMeshes();
	void BuildEntities();

	//Entity* CreateEntity(Mesh*, D3D11Material*, DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);
	Scene* GetScene(int);
	Entity* GetPlayerEntity();

	//Entity* GetAsteroidEntity(int);

private:
	void SetupScenes();
	void SortEntityList(Scene*);

	Scene* scene1;
	Scene* scene2;
	Scene* scene3;
	Scene* scene4;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	D3D11Mesh* cubeMesh;
	D3D11Mesh* quadMesh;
	D3D11Mesh* sphereMesh;
	D3D11Mesh* playerMesh;
	D3D11Mesh* asteroidMesh;
	D3D11Mesh* skyboxMesh;

	
	D3D11Material* creditsMat;
	D3D11Material* menuMat;
	D3D11Material* playerMat;
	D3D11Material* laneMat;
	D3D11Material* asteroidMat;
	D3D11Material* backgroundMat;

	D3D11Material* plutoMat;
	D3D11Material* venusMat;
	D3D11Material* sunMat;
	D3D11Material* earthMat;
	D3D11Material* moonMat;
	D3D11Material* p1Mat;
	D3D11Material* p2Mat;
	D3D11Material* p3Mat;
	D3D11Material* lane2Mat;
	D3D11Material* titleMat;

	D3D11Material* particelMat;

	Entity* playerEnt;

	Entity* laneEnt;
	Entity* laneEnt2;

	GlobalLight* ambient;

	DirectionalLight* dirLight;
	DirectionalLight* dirLight2;
	DirectionalLight* dirLight3;
	DirectionalLight* dirLight4;

	PointLight* pointLight;

	SpotLight* spotLight;

	//Entity* asteroidList[12];
};
