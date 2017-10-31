#pragma once

#include <Windows.h>
#include "Entity.h"
#include "Collider.h"

class Asteroid :
	public Entity
{
public:
	Asteroid();
	~Asteroid();

	Asteroid(Entity* entity);

	void Update(float deltaTime);
	void SetActive(int);

	Collider* GetCollider();

	bool IsActive();
	bool active;
	bool collided = false;

private:
	Entity* entity;
	Collider* asterCollider;

	void Move(float x, float y, float z, float deltaTime);
	void RandomPos();
};

