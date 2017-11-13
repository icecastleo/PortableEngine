#include "RenderSystem.h"
#include "Scene.h"

RenderSystem::RenderSystem()
{
	
}

RenderSystem::~RenderSystem()
{
	
}

void RenderSystem::Update(float deltaTime)
{
	camera->Update(deltaTime);

	for (Entity* ent : scene->entities)
	{
		ent->Update(deltaTime);
	}
}

void RenderSystem::OnResize(uint16_t width, uint16_t height)
{
	camera->Resize(width, height);
}

void RenderSystem::SetScene(Scene *scene)
{
	this->scene = scene;
}
