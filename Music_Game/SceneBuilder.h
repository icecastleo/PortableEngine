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
	void NewScene(int);
<<<<<<< HEAD
	Scene* GetScene(int);
=======
	Scene* GetScene();
	Entity* GetPlayerEntity();
>>>>>>> 68dcfaf344dd0fb7bc16b5c2ae6d1c2165c30622

private:
	void CreateMeshes();
	void CreateEntities(Scene*);

	Scene* scene1;
	Scene* scene2;
	Scene* scene3;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	Mesh* mesh1;
	Mesh* mesh2;
	Mesh* mesh3;

	Material* mat;
	Material* mat2;
	Material* mat3;

	Entity* ent1;
	Entity* ent2;
<<<<<<< HEAD
	Entity* ent3;
=======
	Entity* playerEnt;
>>>>>>> 68dcfaf344dd0fb7bc16b5c2ae6d1c2165c30622

	GlobalLight* ambient;

	DirectionalLight* light;
	DirectionalLight* light2;
	DirectionalLight* light5;
	DirectionalLight* light6;

	PointLight* light3;

	SpotLight* light4;
};