#pragma once
class RenderSystem
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

