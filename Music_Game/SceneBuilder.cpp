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
	delete quadMat;
	delete boxMat;
	delete menuMat;
	delete playerMat;

	delete cubeMesh;
	delete boxMesh;
	delete quadMesh;
	delete playerMesh;

	delete ent1;
	delete ent2;
	delete ent3;
	delete playerEnt;

	delete ambient;
	delete dirLight;
	delete dirLight2;
	delete dirLight3;
	delete dirLight4;
	delete pointLight;
	delete spotLight;

	delete scene1;
	delete scene2;
	delete scene3;

}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init(ID3D11Device *_device, ID3D11DeviceContext *_context)
{
	device = _device;
	context = _context;
	BuildMaterials();
	BuildLights();
	BuildMeshes();
	BuildEntities();
	SetupScenes();
}

//---------------------------------------------------------
//Build Materials Here
//---------------------------------------------------------
void SceneBuilder::BuildMaterials()
{
	const wchar_t* path = L"Assets/textures/quad.png";
	quadMat = new Material(device, context, path);

	path = L"Assets/textures/box.png";
	boxMat = new Material(device, context, path);

	path = L"Assets/textures/menu.png";
	menuMat = new Material(device, context, path);

	path = L"Assets/textures/player.png";
	playerMat = new Material(device, context, path);

	path = L"Assets/textures/asteroid.png";
	asteroidMat = new Material(device, context, path);
}

//---------------------------------------------------------
//Setup lights
//---------------------------------------------------------
void SceneBuilder::BuildLights()
{
	//global ambient light
	ambient = new GlobalLight();
	ambient->AmbientColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1);

	//Directional Lights
	//-----------------------------------------------------------
	dirLight = new DirectionalLight();
	dirLight->DiffuseColor = XMFLOAT4(0, 0, 1, 1);
	dirLight->Direction = XMFLOAT3(1, -1, 0);

	dirLight2 = new DirectionalLight();
	dirLight2->DiffuseColor = XMFLOAT4(1, 0, 0, 1);
	dirLight2->Direction = XMFLOAT3(1, 1, 0);

	dirLight3 = new DirectionalLight();
	dirLight3->DiffuseColor = XMFLOAT4(1, 1, 1, 1);
	dirLight3->Direction = XMFLOAT3(0, 0, 1);

	dirLight4 = new DirectionalLight();
	dirLight4->DiffuseColor = XMFLOAT4(1, 1, 1, 1);
	dirLight4->Direction = XMFLOAT3(0, 0, -1);

	//Point Lights
	//-----------------------------------------------------------
	pointLight = new PointLight();
	pointLight->DiffuseColor = XMFLOAT4(1, 1, 0, 1);
	pointLight->Position = XMFLOAT3(2, 2, -6);

	//Spot Lights
	//-----------------------------------------------------------
	spotLight = new SpotLight();
	spotLight->DiffuseColor = XMFLOAT4(0.85f, 0.85f, 0.85f, 1);
	spotLight->Direction = XMFLOAT3(0, 0, 1);
	spotLight->phi = 0.0f;
	spotLight->Position = XMFLOAT3(0, 0, 0);
	spotLight->theta = 90.0f;
}

//---------------------------------------------------------
//Build Meshes Here
//---------------------------------------------------------
void SceneBuilder::BuildMeshes()
{
	cubeMesh = new Mesh("cube", device);

	boxMesh = new Mesh("box", device);

	quadMesh = new Mesh("quad", device);

	playerMesh = new Mesh("sphere", device);

	asteroidMesh = new Mesh("sphere", device);
}

//---------------------------------------------------------
//Build Base Entities Here
//---------------------------------------------------------
void SceneBuilder::BuildEntities()
{
	ent1 = new Entity(cubeMesh, quadMat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));

	ent2 = new Entity(boxMesh, boxMat, XMFLOAT3(+8.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));

	ent3 = new Entity(quadMesh, menuMat, XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));

	playerEnt = new Entity(playerMesh, playerMat, XMFLOAT3(0.0f, -1.5f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));

	asteroidEnt = new Entity(asteroidMesh, asteroidMat, XMFLOAT3(0.0f, 1.5f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+2.0f, +2.0f, +2.0f));
}

//---------------------------------------------------------
//Setup the 3 built in scenes here
//---------------------------------------------------------
void SceneBuilder::SetupScenes()
{
	//will be for scene 1
	scene1 = new Scene();
	scene1->name = "Menu";
	scene1->entities = std::vector<Entity*>();
	scene1->directionalLights.push_back(dirLight3);
	scene1->entities.push_back(ent3);
	

	//Scene 2
	//------------------------------------------------------------------
	scene2 = new Scene();
	scene2->name = "MainGame";
	scene2->entities = std::vector<Entity*>();
	scene2->globalLights.push_back(ambient);
	scene2->directionalLights.push_back(dirLight);
	scene2->directionalLights.push_back(dirLight2);
	scene2->pointLights.push_back(pointLight);
	scene2->spotLights.push_back(spotLight);
	/*scene2->entities.push_back(ent1);
	scene2->entities.push_back(ent2);*/
	scene2->entities.push_back(playerEnt);
	scene2->entities.push_back(asteroidEnt);
	
	//Scene 3
	//------------------------------------------------------------------
	scene3 = new Scene();
	scene3->name = "Menu";
	scene3->entities = std::vector<Entity*>();
	scene3->directionalLights.push_back(dirLight4);
}


//---------------------------------------------------------
//Create Entities found in the scene
//---------------------------------------------------------
Entity* SceneBuilder::CreateEntity(Mesh* mesh, Material* mat, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	Entity* ent = new Entity(mesh, mat, pos, rot, scale);

	return ent;
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

	return scene1;
}

//---------------------------------------------------------
//Return the player Entity
//---------------------------------------------------------
Entity* SceneBuilder::GetPlayerEntity()
{
	return playerEnt;
}

Entity* SceneBuilder::GetAsteroidEntity()
{
	return asteroidEnt;
}

