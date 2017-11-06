#pragma once
#include "Camera.h"

class RenderSystem
{

protected:
	// init by child
	Camera *camera;

public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void OnResize(uint16_t width, uint16_t height);
};

