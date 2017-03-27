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
	void NewScene();
	Scene* GetScene();
	Entity* GetPlayerEntity();

private:
	void CreateMeshes();
	void CreateEntities();

	Scene* scene1;
	Scene* scene2;
	Scene* scene3;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	Mesh* mesh1;
	Mesh* mesh2;

	Material* mat;
	Material* mat2;

	Entity* ent1;
	Entity* ent2;
	Entity* playerEnt;

	GlobalLight* ambient;

	DirectionalLight* light;
	DirectionalLight* light2;

	PointLight* light3;

	SpotLight* light4;
};