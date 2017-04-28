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
	delete asteroidMat;
	delete menuMat;
	//delete creditsMat;
	delete playerMat;
	delete backgroundMat;
	delete sunMat;
	delete earthMat;
	delete moonMat;
	delete venusMat;

	delete cubeMesh;
	delete asteroidMesh;
	delete sphereMesh;
	delete quadMesh;
	delete playerMesh;

	delete menuEnt;
	delete playerEnt;

	delete menuBackgroundEnt;
	delete gameBackgroundEnt;
	//delete creditsBackgroundEnt;
	delete testNormals;
	delete sunEnt;
	delete earthEnt;
	delete venusEnt;
	delete moonEnt;

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

	for (Entity *e : asteroidList) {
		delete e;
	}
}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init(ID3D11Device *_device, ID3D11DeviceContext *_context)
{
	asteroidList[12];
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
	//Texture file path
	const wchar_t* path;

	path = L"Assets/textures/menu.png";
	menuMat = new Material(device, context, path);

	path = L"Assets/textures/player.png";
	playerMat = new Material(device, context, path);

	//path = L"Assets/textures/asteroid.png";
	path = L"Assets/textures/rock.jpg";
	asteroidMat = new Material(device, context, path);

	path = L"Assets/textures/rockNormals.jpg";
	asteroidMat->SetNormalMap(device, context, path);

	path = L"Assets/textures/pluto.jpg";
	//plutoMat = new Material(device, context, path);

	path = L"Assets/textures/space.jpg";
	//path = L"Assets/textures/SunnyCubeMap.dds";
	backgroundMat = new Material(device, context, path, true);

	path = L"Assets/textures/rainbow.jpg";
	//laneMat = new Material(device, context, path);

	path = L"Assets/textures/venus.png";
	venusMat = new Material(device, context, path);

	path = L"Assets/textures/sun.jpg";
	sunMat = new Material(device, context, path);

	path = L"Assets/textures/earth.jpg";
	earthMat = new Material(device, context, path);

	path = L"Assets/textures/moon.jpg";
	moonMat = new Material(device, context, path);

	path = L"Assets/textures/planet1.jpg";
	p1Mat = new Material(device, context, path);

	path = L"Assets/textures/planet2.png";
	p2Mat = new Material(device, context, path);

	path = L"Assets/textures/planet3.png";
	p3Mat = new Material(device, context, path);

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
	dirLight->DiffuseColor = XMFLOAT4(0, 0, 0, 1);
	dirLight->Direction = XMFLOAT3(-1, -1, -1);

	dirLight2 = new DirectionalLight();
	dirLight2->DiffuseColor = XMFLOAT4(1, 0, 0, 1);
	dirLight2->Direction = XMFLOAT3(1, 1, 0);

	dirLight3 = new DirectionalLight();
	dirLight3->DiffuseColor = XMFLOAT4(1, 1, 1, 1);
	dirLight3->Direction = XMFLOAT3(0, 0, 1);

	dirLight4 = new DirectionalLight();
	dirLight4->DiffuseColor = XMFLOAT4(238.0/255.0, 130.0 / 255.0, 238.0 / 255.0, 1);
	dirLight4->Direction = XMFLOAT3(0, 0, -1);

	//Point Lights
	//-----------------------------------------------------------
	pointLight = new PointLight();
	pointLight->DiffuseColor = XMFLOAT4(1, 1, 0, 1);
	pointLight->Position = XMFLOAT3(2, 2, -6);

	//Spot Lights
	//-----------------------------------------------------------
	spotLight = new SpotLight();
	spotLight->DiffuseColor = XMFLOAT4(0.8f, 0.3f, 0.0f, 1);
	spotLight->Direction = XMFLOAT3(0, 0, 1);
	spotLight->phi = 0.0f;
	spotLight->Position = XMFLOAT3(0, 15, 0);
	spotLight->theta = 90.0f;
}

//---------------------------------------------------------
//Build Meshes Here
//---------------------------------------------------------
void SceneBuilder::BuildMeshes()
{
	cubeMesh = new Mesh("cube", device);
	quadMesh = new Mesh("quad", device);
	sphereMesh = new Mesh("sphere", device);
	playerMesh = new Mesh("sphere", device);
	asteroidMesh = new Mesh("sphereTest", device);
}

//---------------------------------------------------------
//Build Base Entities Here
//---------------------------------------------------------
void SceneBuilder::BuildEntities()
{
	//Entity template (mesh name, material name, position, rotation, scale)

	menuEnt = new Entity(quadMesh, menuMat, XMFLOAT3(+0.0f, +3.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f));

	playerEnt = new Entity(playerMesh, playerMat, XMFLOAT3(0.0f, -1.5f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+2.0f, +2.0f, +2.0f));

	for (int i = 0; i < 12; i++) {
		asteroidList[i]= new Entity(asteroidMesh, asteroidMat, XMFLOAT3(2.0f, 1.5f, -10.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+2.0f, +2.0f, +2.0f));
	}


	menuBackgroundEnt = new Entity(cubeMesh, backgroundMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));
	gameBackgroundEnt = new Entity(cubeMesh, backgroundMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));

	//creditsBackgroundEnt = new Entity(cubeMesh, backgroundMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));

	//laneEnt = new Entity(quadMesh, laneMat, XMFLOAT3(-2.0f, -1.0f, 10.0f), XMFLOAT3(+1.5f, +0.0f, +0.0f), XMFLOAT3(+1.0f, +2.0f, +2.0f));

	testNormals = new Entity(asteroidMesh, asteroidMat, XMFLOAT3(0, 6, -8), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+3.0f, +3.0f, +3.0f));

	venusEnt = new Entity(sphereMesh, venusMat, XMFLOAT3(-60, -10, 30), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+100.0f, +100.0f, +100.0f));
	sunEnt = new Entity(sphereMesh, sunMat, XMFLOAT3(30, -10, 40), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));
	//sunEnt = new Entity(sphereMesh, sunMat, XMFLOAT3(060, 20, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.20f, +0.20f, +0.20f));
	earthEnt = new Entity(sphereMesh, earthMat, XMFLOAT3(1.0f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.5f, +0.5f, +0.5f));
	moonEnt = new Entity(sphereMesh, moonMat, XMFLOAT3(1.0f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.3f, +0.3f, +0.3f));
	p1= new Entity(sphereMesh, p1Mat, XMFLOAT3(0, 0, 1.5f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.7f, +0.7f, +0.7f));
	p2 = new Entity(sphereMesh, p2Mat, XMFLOAT3(-1.5f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.3f, +0.3f, +0.3f));
	p3 = new Entity(sphereMesh, p3Mat, XMFLOAT3(-1.5f, 0, -1), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.6f, +0.6f, +0.6f));

	//sunEnt->SetParent(venusEnt);
	p1->SetParent(sunEnt);
	p2->SetParent(sunEnt);
	p3->SetParent(sunEnt);
	earthEnt->SetParent(sunEnt);
	moonEnt->SetParent(earthEnt);
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
	scene1->globalLights.push_back(ambient);
	scene1->directionalLights.push_back(dirLight3);
	scene1->entities.push_back(menuEnt);
	scene1->background = menuBackgroundEnt;
	//scene1->musicFileName = "04_-_Bloody_Revenge.mp3";
	

	//Scene 2
	//------------------------------------------------------------------
	scene2 = new Scene();
	scene2->name = "MainGame";
	scene2->entities = std::vector<Entity*>();
	scene2->background = gameBackgroundEnt;
	scene2->globalLights.push_back(ambient);
	scene2->entities.push_back(playerEnt);
	for (Entity* e : asteroidList) {
		scene2->entities.push_back(e);
	}
	//scene2->entities.push_back(asteroidEnt5);
	//scene2->entities.push_back(plutoEnt);
	//scene2->entities.push_back(testNormals);
	//
	scene2->entities.push_back(venusEnt);
	scene2->entities.push_back(sunEnt);
	scene2->entities.push_back(earthEnt);
	scene2->entities.push_back(moonEnt);
	scene2->entities.push_back(p1);
	scene2->entities.push_back(p2);
	scene2->entities.push_back(p3);
	scene2->sun = sunEnt;
	scene2->moon = moonEnt;
	scene2->earth = earthEnt;
	scene2->venus = venusEnt;

	scene2->planet1 = p1;
	scene2->planet2 = p2;
	scene2->planet3 = p3;
	//
	scene2->musicFileName = "04_-_Bloody_Revenge.mp3";

	//scene2->spotLights.push_back(spotLight);
	//scene2->directionalLights.push_back(dirLight);
	//scene2->directionalLights.push_back(dirLight2);
	//scene2->directionalLights.push_back(dirLight4);

	
	//Scene 3
	//------------------------------------------------------------------
	scene3 = new Scene();
	scene3->name = "Game Over";
	scene3->entities = std::vector<Entity*>();
	scene3->directionalLights.push_back(dirLight4);
	//scene3->background = creditsBackgroundEnt;
	scene3->musicFileName = "04_-_Bloody_Revenge.mp3";
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
//This needs to go, needs to be requested from the scene itself
//---------------------------------------------------------
Entity* SceneBuilder::GetPlayerEntity()
{
	return playerEnt;
}

Entity* SceneBuilder::GetAsteroidEntity(int num)
{
	return asteroidList[num];
}

