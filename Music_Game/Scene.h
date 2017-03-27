#pragma once
#include "Lights.h"
#include "Entity.h"

struct Scene
{
	std::string name;
	std::vector<Entity*> entities;
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;
	std::vector<GlobalLight*> globalLights;
};