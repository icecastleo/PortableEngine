#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
	for (Entity *entity : entities) {
		delete entity;
	}

	if (skybox)
		delete skybox;
}
