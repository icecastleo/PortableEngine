#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include "Entity.h"
#include "Collider.h"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	Asteroid(Entity* asterEntity);

	void Update(float deltaTime);

	Collider* GetCollider();
private:
	Entity* asterEntity;
	Collider* asterCollider;

	void Move(float x, float y, float z, float deltaTime);
	void RandomPos();
};

