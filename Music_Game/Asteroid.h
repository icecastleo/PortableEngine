#pragma once
#include "Entity.h"
#include <DirectXMath.h>
#include <Windows.h>

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	Asteroid(Entity* asterEntity);

	void Update(float deltaTime);
private:
	Entity* asterEntity;
	void Move(int x, int y, int z, float deltaTime);
	void RandomPos();
};

