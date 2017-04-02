#include "Player.h"

using namespace DirectX;

Player::Player()
{
}

Player::Player(Entity* playerEnt) : playerEntity(playerEnt)
{
	playerCollider = new Collider(playerEntity->GetMesh());
}

Player::~Player()
{
	//delete playerCollider;
}

void Player::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Move(1,0,0,deltaTime);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Move(-1,0,0, deltaTime);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Move(0, 1, 0, deltaTime);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		Move(0, -1, 0, deltaTime);
	}
}

void Player::Move(float x, float y, float z, float deltaTime)
{
	XMVECTOR moveX = XMVectorZero();
	XMVECTOR moveY = XMVectorZero();
	XMVECTOR moveZ = XMVectorZero();
	float moveAmount = 5.0f * deltaTime;

	XMVECTOR fwd = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR right = XMVectorSet(1, 0, 0, 0);

	XMVECTOR pos = XMLoadFloat3(&(playerEntity->GetPosition()));

	moveX = XMVector3Cross(fwd, up);
	moveY = XMVector3Cross(fwd, right);
	moveZ = XMVector3Cross(up, right);
	moveX = moveX * moveAmount;
	moveY = moveY* moveAmount;
	moveZ = moveZ*moveAmount;

	pos += moveX*x + moveY*y + moveZ*z;

	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);

	playerEntity->SetPosition(position);
}

Collider* Player::GetCollider()
{
	return playerCollider;
}