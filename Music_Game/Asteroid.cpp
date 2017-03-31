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
	Move(0, 0, 2,deltaTime);
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
	XMVECTOR pos = XMVectorSet(rand()%4-2, rand() % 5 - 2, 6, 0);
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);
	asterEntity->SetPosition(position);
}

void Asteroid::Move(float x, float y, float z,float deltaTime)
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
	

	pos += moveX*x + moveY*y + moveZ*z;

	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);

	asterEntity->SetPosition(position);
}

