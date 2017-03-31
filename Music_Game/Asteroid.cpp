#include "Asteroid.h"
using namespace DirectX;


Asteroid::Asteroid()
{
}


Asteroid::~Asteroid()
{
}

Asteroid::Asteroid(Entity * asterEntity)
{
	this->asterEntity = asterEntity;
}

void Asteroid::Update(float deltaTime)
{
	Move(0, 0, 1,deltaTime);
	XMVECTOR pos = XMLoadFloat3(&(asterEntity->GetPosition()));
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);
	if (position.z < -3) {
		RandomPos();
	}
	//if
	//random();
	


}

void Asteroid::RandomPos() {
	XMVECTOR pos = XMVectorSet(rand()%4-2, rand() % 4 - 2, 4, 0);
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);
	asterEntity->SetPosition(position);
}

void Asteroid::Move(int x, int y, int z,float deltaTime)
{
	XMVECTOR moveX = XMVectorZero();
	XMVECTOR moveY = XMVectorZero();
	XMVECTOR moveZ = XMVectorZero();
	float moveAmount = 5.0f * deltaTime;

	XMVECTOR fwd = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR right = XMVectorSet(1, 0, 0, 0);

	XMVECTOR pos = XMLoadFloat3(&(asterEntity->GetPosition()));

	moveX = XMVector3Cross(fwd, up);
	moveY = XMVector3Cross(fwd, right);
	moveZ = XMVector3Cross(up, right);
	moveX = moveX * moveAmount;
	moveY = moveY * moveAmount;
	moveZ = moveZ * moveAmount;
	

	if (x == 1)
	{
		pos += moveX;
	}
	else if (x == -1)
	{
		pos -= moveX;
	}

	if (y == 1) {
		pos += moveY;

	}
	else if (y == -1) {
		pos -= moveY;
	}
	if (z == 1) {
		pos += moveZ;
	}
	else if (z == -1) {
		pos -= moveZ;
	}

	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);

	asterEntity->SetPosition(position);
}

