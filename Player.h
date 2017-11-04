#pragma once
//#include <DirectXMath.h>
#include <Windows.h>
#include "Entity.h"

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
	float holdTimer=0;
	bool holdFlag=false;
};

