#pragma once
#include "Camera.h"
#include "Scene.h"

class RenderSystem
{

protected:
	Scene *scene;

	// init by child
	Camera *camera;
public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void Update(float deltaTime);
	virtual void Draw() = 0;

	virtual void SetScene(Scene * scene);
	virtual void OnResize(uint16_t width, uint16_t height);
};

