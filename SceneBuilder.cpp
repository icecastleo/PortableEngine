#include "SceneBuilder.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Engine.h"

SceneBuilder::SceneBuilder() {}

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
}

//---------------------------------------------------------
//Set up a scene
//---------------------------------------------------------
void SceneBuilder::Init()
{
	BuildMaterials();
	BuildLights();
	BuildMeshes();
	SetupScenes();
}

//---------------------------------------------------------
//Build Materials Here
//---------------------------------------------------------
void SceneBuilder::BuildMaterials()
{
	//Texture file path
	const wchar_t* name;

	name = L"player";
	playerMat = Engine::ioSystem->loadTexture2D(name);

	name = L"rock";
	asteroidMat = Engine::ioSystem->loadTexture2D(name, L"rockNormals"); //normal map

	name = L"title";
	menuMat = Engine::ioSystem->loadTexture2D(name);

	name = L"creditsTexture";
	creditsMat = Engine::ioSystem->loadTexture2D(name);

	name = L"spaceBackground";
	backgroundMat = Engine::ioSystem->loadCubemapTexture(name);

	name = L"venus";
	venusMat = Engine::ioSystem->loadTexture2D(name);

	name = L"sun";
	sunMat = Engine::ioSystem->loadTexture2D(name);

	name = L"earth";
	earthMat = Engine::ioSystem->loadTexture2D(name);

	name = L"moon";
	moonMat = Engine::ioSystem->loadTexture2D(name);

	name = L"planet1";
	p1Mat = Engine::ioSystem->loadTexture2D(name);

	name = L"planet2";
	p2Mat = Engine::ioSystem->loadTexture2D(name);

	name = L"planet3";
	p3Mat = Engine::ioSystem->loadTexture2D(name);

	name = L"rainbow3";
	laneMat = Engine::ioSystem->loadTexture2D(name);
	laneMat->UseTransperancy(true);

	name = L"BlueSpace3";
	lane2Mat = Engine::ioSystem->loadTexture2D(name);
	lane2Mat->UseTransperancy(true);

	name = L"titleText";
	titleMat = Engine::ioSystem->loadTexture2D(name);
}

//---------------------------------------------------------
//Setup lights
//---------------------------------------------------------
void SceneBuilder::BuildLights()
{
	//global ambient light
	ambient = new GlobalLight();
	//ambient->AmbientColor = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	ambient->AmbientColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);

	//Directional Lights
	//-----------------------------------------------------------

	//This light is for a no light place holder to be used if a dir light was used before
	//and you don't need one in the current scene.
	dirLight = new DirectionalLight();
	/*dirLight->DiffuseColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	dirLight->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);*/
	dirLight->DiffuseColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	dirLight->Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	dirLight2 = new DirectionalLight();
	/*dirLight2->DiffuseColor = XMFLOAT4(.3f, .3f, .3f, 1);
	dirLight2->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);*/
	dirLight2->DiffuseColor = glm::vec4(.3f, .3f, .3f, 1);
	dirLight2->Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	dirLight3 = new DirectionalLight();
	/*dirLight3->DiffuseColor = XMFLOAT4(.6f, .6f, .6f, 1.0f);
	dirLight3->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);*/
	dirLight3->DiffuseColor = glm::vec4(.6f, .6f, .6f, 1.0f);
	dirLight3->Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	dirLight4 = new DirectionalLight();
	/*dirLight4->DiffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	dirLight4->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);*/
	dirLight4->DiffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	dirLight4->Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	//Point Lights
	//-----------------------------------------------------------
	pointLight = new PointLight();
	/*pointLight->DiffuseColor = XMFLOAT4(0.6f, 1.0f, 1.0f, 1.0f);
	pointLight->Position = XMFLOAT3(20.0f, 20.0f, 20.0f);*/
	pointLight->DiffuseColor = glm::vec4(0.6f, 1.0f, 1.0f, 1.0f);
	pointLight->Position = glm::vec3(20.0f, 20.0f, 20.0f);

	//Spot Lights
	//-----------------------------------------------------------
	spotLight = new SpotLight();
	/*spotLight->DiffuseColor = XMFLOAT4(0.8f, 0.3f, 0.0f, 1);
	spotLight->Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	spotLight->phi = 0.0f;
	spotLight->Position = XMFLOAT3(0.0f, 15.0f, 0.0f);
	spotLight->theta = 90.0f;*/
	spotLight->DiffuseColor = glm::vec4(0.8f, 0.3f, 0.0f, 1);
	spotLight->Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	spotLight->phi = 0.0f;
	spotLight->Position = glm::vec3(0.0f, 15.0f, 0.0f);
	spotLight->theta = 90.0f;
}

//---------------------------------------------------------
//Build Meshes Here
//---------------------------------------------------------
void SceneBuilder::BuildMeshes()
{
	cubeMesh = Engine::ioSystem->loadMesh(L"cube");
	skyboxMesh = Engine::ioSystem->loadMesh(L"cube");
	quadMesh = Engine::ioSystem->loadMesh(L"quad");
	sphereMesh = Engine::ioSystem->loadMesh(L"sphere");
	playerMesh = Engine::ioSystem->loadMesh(L"sphere");
	asteroidMesh = Engine::ioSystem->loadMesh(L"sphere");
}

void SceneBuilder::SetupScenes()
{
	//Scene 1
	//--------------------------------------------------------------------------------------------
	scene1 = new Scene();
	scene1->name = "Menu";

	Entity *background = new Entity(quadMesh, menuMat, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+20.0f, +20.0f, +1.0f));
	scene1->entities.push_back(background);

	Entity *title = new Entity(quadMesh, titleMat, glm::vec3(+0.0f, +5.0f, +0.0f), glm::vec3(+0.2f, +0.0f, +0.0f), glm::vec3(+13.0f, +1.0f, +1.0f));
	scene1->entities.push_back(title);

	//Lights
	scene1->globalLights.push_back(ambient);
	scene1->directionalLights.push_back(dirLight4);

	//Text
	scene1->textList.push_back(textObject{ L"press ENTER to start!", glm::vec2(500, 550) });
	
	//Sound
	//scene1->musicFileName = "";
	
	//End of Scene 1 -----------------------------------------------------------------------------

	//Scene 2
	//--------------------------------------------------------------------------------------------
	scene2 = new Scene();
	scene2->name = "MainGame";
	
	Entity *asteroid = new Entity(asteroidMesh, asteroidMat, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+2.0f, +2.0f, +2.0f));
	asteroid->dirtyUpdate = new Asteroid(asteroid);
	scene2->entities.push_back(asteroid);

	Entity *sun = new Entity(sphereMesh, sunMat, glm::vec3(30, -10, 40), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+10.0f, +10.0f, +10.0f));
	sun->dirtyUpdate = new Planet(sun, 0.1f);
	scene2->entities.push_back(sun);

	Entity *venus = new Entity(sphereMesh, venusMat, glm::vec3(-60, -10, 30), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+100.0f, +100.0f, +100.0f));
	venus->dirtyUpdate = new Planet(venus, 0.005f);
	scene2->entities.push_back(venus);

	Entity *earth = new Entity(sphereMesh, earthMat, glm::vec3(1.0f, 0, 0), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+0.5f, +0.5f, +0.5f));
	earth->dirtyUpdate = new Planet(earth, 0.2f);
	scene2->entities.push_back(earth);

	Entity *moon = new Entity(sphereMesh, moonMat, glm::vec3(1.0f, 0, 0), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+0.3f, +0.3f, +0.3f));
	moon->dirtyUpdate = new Planet(moon, 0.3f);
	scene2->entities.push_back(moon);

	Entity *p1 = new Entity(sphereMesh, p1Mat, glm::vec3(0, 0, 1.5f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+0.7f, +0.7f, +0.7f));
	p1->dirtyUpdate = new Planet(p1, 0.5f);
	scene2->entities.push_back(p1);

	Entity *p2 = new Entity(sphereMesh, p2Mat, glm::vec3(-1.5f, 0, 0), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+0.3f, +0.3f, +0.3f));
	p2->dirtyUpdate = new Planet(p2, -0.4f);
	scene2->entities.push_back(p2);

	Entity *p3 = new Entity(sphereMesh, p3Mat, glm::vec3(-1.5f, 0, -1), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+0.6f, +0.6f, +0.6f));
	p3->dirtyUpdate = new Planet(p3, 0.15f);
	scene2->entities.push_back(p3);

	p1->SetParent(sun);
	p2->SetParent(sun);
	p3->SetParent(sun);
	earth->SetParent(sun);
	moon->SetParent(earth);

	// color lines
	scene2->entities.push_back(new Entity(quadMesh, lane2Mat, glm::vec3(-3.0f, -1.2f, 8.0f), glm::vec3(+90.0, -0.0f, +0.0f), glm::vec3(+1.0f, +14.0f, +1.0f)));
	scene2->entities.push_back(new Entity(quadMesh, laneMat, glm::vec3(3.0f, -1.2f, 8.0f), glm::vec3(+90.0f, -0.0f, +0.0f), glm::vec3(+1.0f, +14.0f, +1.0f)));

	//Background
	scene2->skybox = new Entity(skyboxMesh, backgroundMat, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+10.0f, +10.0f, +10.0f));

	//Lights
	scene2->globalLights.push_back(ambient);
	scene2->pointLights.push_back(pointLight);
	scene2->directionalLights.push_back(dirLight);

	//Sound
	scene2->musicFileName = "04_-_Bloody_Revenge.mp3";

	//2D Text
	scene2->textList.push_back(textObject{ L"Score: ", glm::vec2(500, 10) });

	//End of Scene 2 -----------------------------------------------------------------------------

	//Scene 3
	//--------------------------------------------------------------------------------------------
	scene3 = new Scene();
	scene3->name = "Results";

	//Background
	scene3->entities.push_back(new Entity(quadMesh, creditsMat, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+20.0f, +20.0f, +1.0f)));

	//Lights
	scene3->globalLights.push_back(ambient);
	scene3->directionalLights.push_back(dirLight4);

	//2D Text
	scene3->textList.push_back(textObject{ L"Results", glm::vec2(580, 300) });
	scene3->textList.push_back(textObject{ L"You Scored: ", glm::vec2(530, 350) });

	//End of Scene 3 -----------------------------------------------------------------------------

	//Scene 4
	//--------------------------------------------------------------------------------------------
	scene4 = new Scene();
	scene4->name = "Credits";

	//Background
	scene4->entities.push_back(new Entity(quadMesh, creditsMat, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(+0.0f, +0.0f, +0.0f), glm::vec3(+20.0f, +20.0f, +1.0f)));

	//Lights
	scene4->globalLights.push_back(ambient);
	scene4->directionalLights.push_back(dirLight4);

	//2D Text
	scene4->textList.push_back(textObject{ L"Credits", glm::vec2(600, 10) });

	scene4->textList.push_back(textObject{ L"Designers & Developers", glm::vec2(500, 50) });
	scene4->textList.push_back(textObject{ L"Shih-Kuang Chu", glm::vec2(550, 90) });
	scene4->textList.push_back(textObject{ L"Darren Farr", glm::vec2(580, 130) });
	scene4->textList.push_back(textObject{ L"Rahul Madhyan", glm::vec2(560, 170) });
	scene4->textList.push_back(textObject{ L"Pengfei Zhang", glm::vec2(562, 210) });

	scene4->textList.push_back(textObject{ L"Models provided by Chris Cascioli", glm::vec2(430, 300) });
	scene4->textList.push_back(textObject{ L"Textures by Google Search", glm::vec2(450, 350) });

	scene4->textList.push_back(textObject{ L"Sound from FreeMusicArchive.org", glm::vec2(430, 400) });
	scene4->textList.push_back(textObject{ L"Bloody Revenge", glm::vec2(580, 450) });
	scene4->textList.push_back(textObject{ L"Hypnagogic", glm::vec2(580, 500) });

	//End of Scene 4 -----------------------------------------------------------------------------

	//Sort the entities in the scenes
	SortEntityList(scene1);
	SortEntityList(scene2);
	SortEntityList(scene3);
	SortEntityList(scene4);
}

// TODO: Change??
void SceneBuilder::SortEntityList(Scene* s)
{
	for (unsigned int i = 0; i < s->entities.size(); i++)
	{
		if (s->entities.at(i)->GetMat()->UseTransperancy())
		{
			s->transparent.push_back(s->entities.at(i));
		}
		else
		{
			s->opaque.push_back(s->entities.at(i));
		}
	}
}

Scene* SceneBuilder::GetScene(int num)
{
	if (num == 1) { return scene1; }
	else if (num == 2) { return scene2; }
	else if (num == 3) { return scene3; }
	else if (num == 4) { return scene4; }
	else { return nullptr; }
}