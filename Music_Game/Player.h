#pragma once
#include "Entity.h"
#include <DirectXMath.h>
#include <Windows.h>

class Player
{
public:
	Player();
	Player(Entity* playerEnt);
	~Player();

	void Update(float deltaTime);

private:
	Entity* playerEntity;
	void Move(float x, float y, float z, float deltaTime);
};

