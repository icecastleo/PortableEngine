//Darren Farr
#pragma once
#include "Entity.h"
#include <DirectXMath.h>
#include "Mesh.h"
#include "Material.h"
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


	Entity* CreateEntity(Mesh*, Material*, DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);
	Scene* GetScene(int);
	Entity* GetPlayerEntity();
	Entity* GetAsteroidEntity(int);
	

private:
	void SetupScenes();

	Scene* scene1;
	Scene* scene2;
	Scene* scene3;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	Mesh* cubeMesh;
	Mesh* quadMesh;
	Mesh* sphereMesh;
	Mesh* playerMesh;
	Mesh* asteroidMesh;
	
	//Material* creditsMat;
	Material* menuMat;
	Material* playerMat;
	Material* asteroidMat;
	Material* backgroundMat;
	Material* laneMat;
	Material* plutoMat;
	Material* venusMat;
	Material* sunMat;
	Material* earthMat;
	Material* moonMat;

	Entity* menuEnt;
	Entity* menuBackgroundEnt;
	Entity* gameBackgroundEnt;
	//Entity* creditsBackgroundEnt;
	Entity* playerEnt;


	Entity* laneEnt;
	Entity* plutoEnt;
	Entity* testNormals;
	Entity* venusEnt;
	Entity* sunEnt;
	Entity* moonEnt;
	Entity* earthEnt;


	GlobalLight* ambient;

	DirectionalLight* dirLight;
	DirectionalLight* dirLight2;
	DirectionalLight* dirLight3;
	DirectionalLight* dirLight4;

	PointLight* pointLight;

	SpotLight* spotLight;

	Entity* asteroidList[12];
};