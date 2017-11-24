#pragma once
//#include "Lights.h"
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

	void Init();
	void BuildMaterials();
	void BuildLights();
	void BuildMeshes();

	Scene* GetScene(int);

private:
	void SetupScenes();
	void SortEntityList(Scene*);

	Scene* scene1;
	Scene* scene2;
	Scene* scene3;
	Scene* scene4;

	Mesh* cubeMesh;
	Mesh* quadMesh;
	Mesh* sphereMesh;
	Mesh* playerMesh;
	Mesh* asteroidMesh;
	Mesh* skyboxMesh;

	Material* creditsMat;
	//Material* menuMat;
	Material* playerMat;
	Material* laneMat;
	Material* asteroidMat;
	Material* backgroundMat;

	Material* plutoMat;
	Material* venusMat;
	Material* sunMat;
	Material* earthMat;
	Material* moonMat;
	Material* p1Mat;
	Material* p2Mat;
    Material* p3Mat;
	Material* lane2Mat;
	//Material* titleMat;

	Entity* laneEnt;
	Entity* laneEnt2;

	GlobalLight* ambient;

	DirectionalLight* dirLight;
	DirectionalLight* dirLight2;
	DirectionalLight* dirLight3;
	DirectionalLight* dirLight4;

	PointLight* pointLight;

	SpotLight* spotLight;
};
