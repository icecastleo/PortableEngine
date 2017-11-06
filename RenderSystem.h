#pragma once
#include "Camera.h"

class RenderSystem
{

protected:
	Camera * Cam;
	
public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

