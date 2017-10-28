#pragma once

#include "Lights.h"
#include "Text.h"
#include "Entity.h"
#include "Emitter.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::string name;

	std::vector<Entity*> entities;
	std::vector<Entity*> opaque;
	std::vector<Entity*> transparent;
	std::vector<Entity*> opaqueNorm;
	std::vector<Entity*> transparentNorm;

	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;
	std::vector<GlobalLight*> globalLights;

	std::vector<textObject> textList;

	Entity* skybox = nullptr;
	Emitter* Particles = nullptr;

	char *musicFileName = 0;

	void Update(float deltaTime);

private:

};

