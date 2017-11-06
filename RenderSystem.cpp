#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
	
}

RenderSystem::~RenderSystem()
{
	
}

void RenderSystem::OnResize(uint16_t width, uint16_t height)
{
	camera->Resize(width, height);
}
