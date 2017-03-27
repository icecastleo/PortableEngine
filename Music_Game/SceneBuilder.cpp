//Darren Farr
#include "SceneBuilder.h"

using namespace DirectX;

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
SceneBuilder::SceneBuilder() {}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
SceneBuilder::~SceneBuilder()
{
	delete mat;
	delete mat2;
	delete mesh1;
	delete mesh2;
	delete ent1;
	delete ent2;
	delete ambient;
	delete light;
	delete light2;
	delete light3;
	delete light4;
	delete scene1;

}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init(ID3D11Device *_device, ID3D11DeviceContext *_context)
{
	device = _device;
	context = _context;
	scene1 = new Scene();
	scene1->name = "Test";
	scene1->entities = std::vector<Entity*>();


	const wchar_t* path = L"Assets/textures/quad.png";
	mat = new Material(device, context, path);

	path = L"Assets/textures/box.png";
	mat2 = new Material(device, context, path);

	ambient = new GlobalLight();
	ambient->AmbientColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1);
	scene1->globalLights.push_back(ambient);

	light = new DirectionalLight();
	light->DiffuseColor = XMFLOAT4(0, 0, 1, 1);
	light->Direction = XMFLOAT3(1, -1, 0);
	scene1->directionalLights.push_back(light);

	light2 = new DirectionalLight();
	light2->DiffuseColor = XMFLOAT4(1, 0, 0, 1);
	light2->Direction = XMFLOAT3(1, 1, 0);
	scene1->directionalLights.push_back(light2);

	light3 = new PointLight();
	light3->DiffuseColor = XMFLOAT4(1, 1, 0, 1);
	light3->Position = XMFLOAT3(2, 2, -6);
	scene1->pointLights.push_back(light3);

	light4 = new SpotLight();
	light4->DiffuseColor = XMFLOAT4(0.85f, 0.85f, 0.85f, 1);
	light4->Direction = XMFLOAT3(0, 0, 1);
	light4->phi = 0.0f;
	light4->Position = XMFLOAT3(0, 0, 0);
	light4->theta = 90.0f;
	scene1->spotLights.push_back(light4);

	CreateMeshes();
	CreateEntities();
}

//---------------------------------------------------------
//Sets up new scenes
//may or may not be used later for better structering
//---------------------------------------------------------
void SceneBuilder::NewScene(int sceneNum) 
{
	//will be for scene 1
	
	//Scene 2
	
	
	//Scene 3
}

//---------------------------------------------------------
//Create Meshes based on an imported model
//---------------------------------------------------------
void SceneBuilder::CreateMeshes()
{
	//Load a model from file
	mesh1 = new Mesh("cube", device);

	mesh2 = new Mesh("box", device);
}

//---------------------------------------------------------
//Create Entities found in the scene
//---------------------------------------------------------
void SceneBuilder::CreateEntities()
{
	ent1 = new Entity(mesh1, mat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene1->entities.push_back(ent1);
	//scene.push_back(new Entity(mesh3, mat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f)) );

	ent2 = new Entity(mesh2, mat2, XMFLOAT3(+8.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene1->entities.push_back(ent2);

	playerEnt = new Entity(mesh2, mat, XMFLOAT3(0.0f, -4.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene1->entities.push_back(playerEnt);
}

//---------------------------------------------------------
//Return the list of entities in the scene
//---------------------------------------------------------
Scene* SceneBuilder::GetScene()
{
	return scene1;
}

Entity* SceneBuilder::GetPlayerEntity()
{
	return playerEnt;
}