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
	delete mat3;
	delete mesh1;
	delete mesh2;
	delete ent1;
	delete ent2;
	delete ambient;
	delete light;
	delete light2;
	delete light3;
	delete light4;
	delete light5;
	delete light6;
	delete scene1;

}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init(ID3D11Device *_device, ID3D11DeviceContext *_context)
{
	device = _device;
	context = _context;
	NewScene(0);
}

//---------------------------------------------------------
//Sets up new scenes
//may or may not be used later for better structering
//---------------------------------------------------------
void SceneBuilder::NewScene(int sceneNum) 
{
	//will be for scene 1
	scene1 = new Scene();
	scene1->name = "Menu";
	scene1->entities = std::vector<Entity*>();

	const wchar_t* path = L"Assets/textures/menu.png";
	mat3 = new Material(device, context, path);

	light5 = new DirectionalLight();
	light5->DiffuseColor = XMFLOAT4(1, 1, 1, 1);
	light5->Direction = XMFLOAT3(0, 0, -1);
	scene1->directionalLights.push_back(light5);

	mesh3 = new Mesh("quad", device);

	ent3 = new Entity(mesh3, mat3, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene1->entities.push_back(ent3);
	
	//Scene 2
	//------------------------------------------------------------------
	scene2 = new Scene();
	scene2->name = "MainGame";
	scene2->entities = std::vector<Entity*>();


	path = L"Assets/textures/quad.png";
	mat = new Material(device, context, path);

	path = L"Assets/textures/box.png";
	mat2 = new Material(device, context, path);

	ambient = new GlobalLight();
	ambient->AmbientColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1);
	scene2->globalLights.push_back(ambient);

	light = new DirectionalLight();
	light->DiffuseColor = XMFLOAT4(0, 0, 1, 1);
	light->Direction = XMFLOAT3(1, -1, 0);
	scene2->directionalLights.push_back(light);

	light2 = new DirectionalLight();
	light2->DiffuseColor = XMFLOAT4(1, 0, 0, 1);
	light2->Direction = XMFLOAT3(1, 1, 0);
	scene2->directionalLights.push_back(light2);

	light3 = new PointLight();
	light3->DiffuseColor = XMFLOAT4(1, 1, 0, 1);
	light3->Position = XMFLOAT3(2, 2, -6);
	scene2->pointLights.push_back(light3);

	light4 = new SpotLight();
	light4->DiffuseColor = XMFLOAT4(0.85f, 0.85f, 0.85f, 1);
	light4->Direction = XMFLOAT3(0, 0, 1);
	light4->phi = 0.0f;
	light4->Position = XMFLOAT3(0, 0, 0);
	light4->theta = 90.0f;
	scene2->spotLights.push_back(light4);

	mesh1 = new Mesh("cube", device);

	mesh2 = new Mesh("box", device);

	ent1 = new Entity(mesh1, mat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene2->entities.push_back(ent1);
	//scene.push_back(new Entity(mesh3, mat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f)) );

	ent2 = new Entity(mesh2, mat2, XMFLOAT3(+8.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));
	scene2->entities.push_back(ent2);

	//CreateMeshes();
	//CreateEntities(scene2);
	
	//Scene 3
	scene3 = new Scene();
	scene3->name = "Menu";
	scene3->entities = std::vector<Entity*>();

	light6 = new DirectionalLight();
	light6->DiffuseColor = XMFLOAT4(1, 1, 1, 1);
	light6->Direction = XMFLOAT3(0, 0, -1);
	scene3->directionalLights.push_back(light6);
}

//---------------------------------------------------------
//Create Meshes based on an imported model
//---------------------------------------------------------
void SceneBuilder::CreateMeshes()
{
	//Load a model from file
	
}

//---------------------------------------------------------
//Create Entities found in the scene
//---------------------------------------------------------
void SceneBuilder::CreateEntities(Scene* s)
{
	
}

//---------------------------------------------------------
//Return the list of entities in the scene
//---------------------------------------------------------
Scene* SceneBuilder::GetScene(int num)
{
	if (num == 1) { return scene1; }
	else if (num == 2) { return scene2; }
	else if (num == 3) { return scene3; }
	else { return nullptr; }
}