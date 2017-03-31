#include "Player.h"

using namespace DirectX;

Player::Player()
{
}

Player::Player(Entity* playerEnt) : playerEntity(playerEnt)
{

}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Move(1, deltaTime);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Move(-1, deltaTime);
	}
}

void Player::Move(int direction, float deltaTime)
{
	XMVECTOR moveDir = XMVectorZero();
	float moveAmount = 5.0f * deltaTime;

	XMVECTOR fwd = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	XMVECTOR pos = XMLoadFloat3(&(playerEntity->GetPosition()));

	moveDir = XMVector3Cross(fwd, up);
	moveDir = moveDir * moveAmount;

	if (direction == 1)
	{
		pos += moveDir;
	}
	else if (direction == -1)
	{
		pos -= moveDir;
	}
	
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);

	playerEntity->SetPosition(position);
}