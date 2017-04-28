#pragma once
#include "Lights.h"
#include "Entity.h"

struct Scene
{
	std::string name;
	std::vector<Entity*> entities;
	Entity* background;
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;
	std::vector<GlobalLight*> globalLights;

	Entity* sun;
	Entity* moon;
	Entity* earth;
	Entity* venus;
	Entity* planet1;
	Entity* planet2;
	Entity* planet3;

	char *musicFileName = 0;
};