//Darren Farr
#include "SceneBuilder.h"
#include "Asteroid.h"
#include "Planet.h"

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
	delete creditsMat;
	delete playerMat;
	delete backgroundMat;
	delete sunMat;
	delete earthMat;
	delete moonMat;
	delete venusMat;
	delete laneMat;
	delete p1Mat;
	delete p2Mat;
	delete p3Mat;
	delete lane2Mat;
	delete particelMat;
	delete titleMat;

	delete cubeMesh;
	delete asteroidMesh;
	delete sphereMesh;
	delete quadMesh;
	delete playerMesh;
	delete skyboxMesh;

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
	delete scene4;

	//for (Entity *e : asteroidList) {
	//	delete e;
	//}

	delete emitter;
}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init(ID3D11Device *_device, ID3D11DeviceContext *_context)
{
	//asteroidList[12];
	device = _device;
	context = _context;
	BuildMaterials();
	BuildLights();
	BuildMeshes();
	BuildParticles();
	SetupScenes();
}

//---------------------------------------------------------
//Build Materials Here
//---------------------------------------------------------
void SceneBuilder::BuildMaterials()
{
	//Texture file path
	const wchar_t* path;

	path = L"Assets/textures/player.png";
	playerMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/rock.jpg";
	asteroidMat = new D3D11Material(device, context, path);
	path = L"Assets/textures/rockNormals.jpg";
	asteroidMat->SetNormalMap(device, context, path);

	path = L"Assets/textures/title.png";
	menuMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/creditsTexture.jpg";
	creditsMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/spaceBackground.dds";
	backgroundMat = new D3D11Material(device, context, path, 0);

	path = L"Assets/textures/venus.jpg";
	venusMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/sun.jpg";
	sunMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/earth.png";
	earthMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/moon.jpg";
	moonMat = new D3D11Material(device, context, path);

	path = L"Assets/textures/planet1.jpg";
	p1Mat = new D3D11Material(device, context, path);

	path = L"Assets/textures/planet2.png";
	p2Mat = new D3D11Material(device, context, path);

	path = L"Assets/textures/planet3.png";
	p3Mat = new D3D11Material(device, context, path);

	path = L"Assets/textures/rainbow3.png";
	laneMat = new D3D11Material(device, context, path);
	laneMat->UseTransperancy(true);

	path = L"Assets/textures/blueSpace3.png";
	lane2Mat = new D3D11Material(device, context, path);
	lane2Mat->UseTransperancy(true);

	path = L"Assets/Textures/circleParticle.jpg"; 
	particelMat = new D3D11Material(device, context, path, 1);

	path = L"Assets/Textures/titleText.png";
	titleMat = new D3D11Material(device, context, path);

}

//---------------------------------------------------------
//Setup lights
//---------------------------------------------------------
void SceneBuilder::BuildLights()
{
	//global ambient light
	ambient = new GlobalLight();
	ambient->AmbientColor = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);

	//Directional Lights
	//-----------------------------------------------------------

	//This light is for a no light place holder to be used if a dir light was used before
	//and you don't need one in the current scene.
	dirLight = new DirectionalLight();
	dirLight->DiffuseColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	dirLight->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

	dirLight2 = new DirectionalLight();
	dirLight2->DiffuseColor = XMFLOAT4(.3f, .3f, .3f, 1);
	dirLight2->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

	dirLight3 = new DirectionalLight();
	dirLight3->DiffuseColor = XMFLOAT4(.6f, .6f, .6f, 1.0f);
	dirLight3->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

	dirLight4 = new DirectionalLight();
	dirLight4->DiffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	dirLight4->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

	//Point Lights
	//-----------------------------------------------------------
	pointLight = new PointLight();
	pointLight->DiffuseColor = XMFLOAT4(0.6f, 1.0f, 1.0f, 1.0f);
	pointLight->Position = XMFLOAT3(20.0f, 20.0f, 20.0f);

	//Spot Lights
	//-----------------------------------------------------------
	spotLight = new SpotLight();
	spotLight->DiffuseColor = XMFLOAT4(0.8f, 0.3f, 0.0f, 1);
	spotLight->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	spotLight->phi = 0.0f;
	spotLight->Position = XMFLOAT3(0.0f, 15.0f, 0.0f);
	spotLight->theta = 90.0f;
}

//---------------------------------------------------------
//Build Meshes Here
//---------------------------------------------------------
void SceneBuilder::BuildMeshes()
{

	cubeMesh = new D3D11Mesh(L"cube", device, false);

	skyboxMesh = new D3D11Mesh(L"cube", device, true);

	quadMesh = new D3D11Mesh(L"quad", device, false);

	sphereMesh = new D3D11Mesh(L"sphere", device, false);

	playerMesh = new D3D11Mesh(L"sphere", device, false);

	asteroidMesh = new D3D11Mesh(L"sphereTest", device, true);
}

//---------------------------------------------------------
//Build Base Entities Here
//---------------------------------------------------------
void SceneBuilder::BuildEntities()
{
	//Entity template (mesh name, material name, position, rotation, scale)
	playerEnt = new Entity(playerMesh, playerMat, XMFLOAT3(0.0f, -1.5f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+2.0f, +2.0f, +2.0f));
}

void SceneBuilder::BuildParticles()
{
	emitter = new Emitter(
		200,							// Max particles
		200,							// Particles per second
		0.5f,							// Particle lifetime
		0.25f,							// Start size
		2.0f,							// End size
		XMFLOAT4(1, 0.1f, 0.1f, 0.2f),	// Start color
		XMFLOAT4(1, 1.0f, 1.0f, 0),		// End color
		XMFLOAT3(10, 10, 0),			// Start velocity
		XMFLOAT3(0, 0, 0),				// Start position
		XMFLOAT3(10, 10, 0),			// Start acceleration
		device,
		particelMat);
}

//---------------------------------------------------------
//Setup the 3 built in scenes here
//---------------------------------------------------------
void SceneBuilder::SetupScenes()
{
	//Scene 1
	//--------------------------------------------------------------------------------------------
	scene1 = new Scene();
	scene1->name = "Menu";

	Entity *background = new Entity(quadMesh, menuMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+20.0f, +20.0f, +1.0f));
	scene1->entities.push_back(background);

	Entity *title = new Entity(quadMesh, titleMat, XMFLOAT3(+0.0f, +5.0f, +0.0f), XMFLOAT3(+0.2f, +0.0f, +0.0f), XMFLOAT3(+13.0f, +1.0f, +1.0f));
	scene1->entities.push_back(title);

	//Lights
	scene1->globalLights.push_back(ambient);
	scene1->directionalLights.push_back(dirLight4);

	//Text
	scene1->textList.push_back(textObject{ L"press ENTER to start!", DirectX::XMFLOAT2(500, 550) });
	
	//Sound
	//scene1->musicFileName = "";
	
	//End of Scene 1 -----------------------------------------------------------------------------

	//Scene 2
	//--------------------------------------------------------------------------------------------
	scene2 = new Scene();
	scene2->name = "MainGame";
	
	for (int i = 0; i < 12; i++) {
		Entity *entity = new Entity(asteroidMesh, asteroidMat, XMFLOAT3(2.0f, 1.5f, -10.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+2.0f, +2.0f, +2.0f));
		entity->dirtyUpdate = new Asteroid(entity);
		scene2->entities.push_back(entity);
	}

	//scene2->entities.push_back(playerEnt);

	Entity *sun = new Entity(sphereMesh, sunMat, XMFLOAT3(30, -10, 40), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));
	sun->dirtyUpdate = new Planet(sun, 0.002f);
	scene2->entities.push_back(sun);

	Entity *venus = new Entity(sphereMesh, venusMat, XMFLOAT3(-60, -10, 30), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+100.0f, +100.0f, +100.0f));
	venus->dirtyUpdate = new Planet(venus, 0.0001f);
	scene2->entities.push_back(venus);

	Entity *earth = new Entity(sphereMesh, earthMat, XMFLOAT3(1.0f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.5f, +0.5f, +0.5f));
	earth->dirtyUpdate = new Planet(earth, 0.004f);
	scene2->entities.push_back(earth);

	Entity *moon = new Entity(sphereMesh, moonMat, XMFLOAT3(1.0f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.3f, +0.3f, +0.3f));
	moon->dirtyUpdate = new Planet(moon, 0.006f);
	scene2->entities.push_back(moon);

	Entity *p1 = new Entity(sphereMesh, p1Mat, XMFLOAT3(0, 0, 1.5f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.7f, +0.7f, +0.7f));
	p1->dirtyUpdate = new Planet(p1, 0.01f);
	scene2->entities.push_back(p1);

	Entity *p2 = new Entity(sphereMesh, p2Mat, XMFLOAT3(-1.5f, 0, 0), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.3f, +0.3f, +0.3f));
	p2->dirtyUpdate = new Planet(p2, -0.008f);
	scene2->entities.push_back(p2);

	Entity *p3 = new Entity(sphereMesh, p3Mat, XMFLOAT3(-1.5f, 0, -1), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+0.6f, +0.6f, +0.6f));
	p3->dirtyUpdate = new Planet(p3, 0.003f);
	scene2->entities.push_back(p3);

	p1->SetParent(sun);
	p2->SetParent(sun);
	p3->SetParent(sun);
	earth->SetParent(sun);
	moon->SetParent(earth);

	// color lines
	scene2->entities.push_back(new Entity(quadMesh, lane2Mat, XMFLOAT3(-2.8f, -1.2f, 8.0f), XMFLOAT3(+1.6f, -0.1f, +0.0f), XMFLOAT3(+1.0f, +14.0f, +1.0f)));
	scene2->entities.push_back(new Entity(quadMesh, laneMat, XMFLOAT3(1.5f, -1.2f, 8.0f), XMFLOAT3(+1.6f, -0.1f, +0.0f), XMFLOAT3(+1.0f, +14.0f, +1.0f)));

	//Background
	scene2->skybox = new Entity(skyboxMesh, backgroundMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+10.0f, +10.0f, +10.0f));

	//Lights
	scene2->globalLights.push_back(ambient);
	scene2->pointLights.push_back(pointLight);
	scene2->directionalLights.push_back(dirLight);

	//Sound
	scene2->musicFileName = "04_-_Bloody_Revenge.mp3";

	//Particles
	scene2->Particles = emitter;

	//2D Text
	scene2->textList.push_back(textObject{ L"Score: ", DirectX::XMFLOAT2(500, 10) });

	//End of Scene 2 -----------------------------------------------------------------------------

	//Scene 3
	//--------------------------------------------------------------------------------------------
	scene3 = new Scene();
	scene3->name = "Results";

	//Background
	scene3->entities.push_back(new Entity(quadMesh, creditsMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+20.0f, +20.0f, +1.0f)));

	//Lights
	scene3->globalLights.push_back(ambient);
	scene3->directionalLights.push_back(dirLight4);

	//2D Text
	scene3->textList.push_back(textObject{ L"Results", DirectX::XMFLOAT2(580, 300) });
	scene3->textList.push_back(textObject{ L"You Scored: ", DirectX::XMFLOAT2(530, 350) });

	//End of Scene 3 -----------------------------------------------------------------------------

	//Scene 4
	//--------------------------------------------------------------------------------------------
	scene4 = new Scene();
	scene4->name = "Credits";

	//Background
	scene4->entities.push_back(new Entity(quadMesh, creditsMat, XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(+20.0f, +20.0f, +1.0f)));

	//Lights
	scene4->globalLights.push_back(ambient);
	scene4->directionalLights.push_back(dirLight4);

	//2D Text
	scene4->textList.push_back(textObject{ L"Credits", DirectX::XMFLOAT2(600, 10) });

	scene4->textList.push_back(textObject{ L"Designers & Developers", DirectX::XMFLOAT2(500, 50) });
	scene4->textList.push_back(textObject{ L"Shih-Kuang Chu", DirectX::XMFLOAT2(550, 90) });
	scene4->textList.push_back(textObject{ L"Darren Farr", DirectX::XMFLOAT2(580, 130) });
	scene4->textList.push_back(textObject{ L"Rahul Madhyan", DirectX::XMFLOAT2(560, 170) });
	scene4->textList.push_back(textObject{ L"Pengfei Zhang", DirectX::XMFLOAT2(562, 210) });

	scene4->textList.push_back(textObject{ L"Models provided by Chris Cascioli", DirectX::XMFLOAT2(430, 300) });
	scene4->textList.push_back(textObject{ L"Textures by Google Search", DirectX::XMFLOAT2(450, 350) });

	scene4->textList.push_back(textObject{ L"Sound from FreeMusicArchive.org", DirectX::XMFLOAT2(430, 400) });
	scene4->textList.push_back(textObject{ L"Bloody Revenge", DirectX::XMFLOAT2(580, 450) });
	scene4->textList.push_back(textObject{ L"Hypnagogic", DirectX::XMFLOAT2(580, 500) });

	//End of Scene 4 -----------------------------------------------------------------------------

	//Sort the entities in the scenes
	SortEntityList(scene1);
	SortEntityList(scene2);
	SortEntityList(scene3);
	SortEntityList(scene4);
}


//---------------------------------------------------------
//Create Entities found in the scene
//---------------------------------------------------------
/*Entity* SceneBuilder::CreateEntity(Mesh* mesh, D3D11Material* mat, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	Entity* ent = new Entity(mesh, mat, pos, rot, scale);

	return ent;
}*/

//---------------------------------------------------------
//Sort the entities lists into opaque or transparent lists, with or without normal maps
//---------------------------------------------------------
void SceneBuilder::SortEntityList(Scene* s)
{
	for (unsigned int i = 0; i < s->entities.size(); i++)
	{
		if (s->entities.at(i)->GetMat()->UseTransperancy() && s->entities.at(i)->GetMat()->HasNormalMap())
		{
			s->transparentNorm.push_back(s->entities.at(i));
		}
		else if (s->entities.at(i)->GetMat()->UseTransperancy())
		{
			s->transparent.push_back(s->entities.at(i));
		}
		else if (s->entities.at(i)->GetMat()->HasNormalMap())
		{
			s->opaqueNorm.push_back(s->entities.at(i));
		}
		else
		{
			s->opaque.push_back(s->entities.at(i));
		}
	}
}

//---------------------------------------------------------
//Return the list of entities in the scene
//---------------------------------------------------------
Scene* SceneBuilder::GetScene(int num)
{
	if (num == 1) { return scene1; }
	else if (num == 2) { return scene2; }
	else if (num == 3) { return scene3; }
	else if (num == 4) { return scene4; }
	else { return nullptr; }
}

//---------------------------------------------------------
//Return the player Entity
//This needs to go, needs to be requested from the scene itself
//---------------------------------------------------------
Entity* SceneBuilder::GetPlayerEntity()
{
	return playerEnt;
}

//Entity* SceneBuilder::GetAsteroidEntity(int num)
//{
//	return asteroidList[num];
//}

