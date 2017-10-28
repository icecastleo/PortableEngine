#pragma once
#include "Entity.h"
class Planet :
	public Entity
{
public:
	Planet(Entity *entity, float rotation);
	~Planet();

	void Update(float deltaTime);

private:
	Entity *entity;
	float rotation;
};

