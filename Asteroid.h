#pragma once

//#include <Windows.h>
#include "Entity.h"


class Asteroid :
	public Entity
{
public:
	Asteroid();
	~Asteroid();

	Asteroid(Entity* entity);

	void Update(float deltaTime);
	void SetActive(int);

	bool IsActive();
	bool active;
	bool collided = false;

private:
	Entity* entity;

	void Move(float x, float y, float z, float deltaTime);
	void RandomPos();
};

