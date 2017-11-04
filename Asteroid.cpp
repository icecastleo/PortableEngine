#include "Asteroid.h"
using namespace DirectX;

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(Entity * entity)
{
	this->entity = entity;
	active = false;
}

void Asteroid::Update(float deltaTime)
{
	if (active)
	{
		Move(-0.2f, 0, 2, deltaTime);
		/*XMVECTOR pos = XMLoadFloat3(&(entity->GetPosition()));
		XMFLOAT3 position;
		XMFLOAT3 rota = entity->GetRotation();*/
		glm::vec3 pos = entity->GetPosition();
		glm::vec3 position;
		glm::vec3 rota = entity->GetRotation();
		rota.y += (rand() % 3)*0.005f;
		rota.x += (rand() % 3)*0.005f;
		rota.z += (rand() % 3)*0.005f;
		//rota.y += 0.005f;
		entity->SetRotation(rota);

		//XMStoreFloat3(&position, pos);
		position = pos;
		if (position.z < -10) {
			active = false;
		}

		if (position.z < -1.0f) {
			collided = true;			
		}
	}
}

void Asteroid::RandomPos() {
	/*XMVECTOR pos = XMVectorSet(rand()%4-2, rand() % 5 - 2, 20, 0);
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);*/

	glm::vec4 pos = glm::vec4(rand() % 4 - 2, rand() % 5 - 2, 20, 0);
	glm::vec3 position;
	//XMStoreFloat3(&position, pos);
	position = glm::vec3(pos);
	entity->SetPosition(position);
}

void Asteroid::Move(float x, float y, float z,float deltaTime)
{
	/*XMVECTOR moveX = XMVectorZero();
	XMVECTOR moveY = XMVectorZero();
	XMVECTOR moveZ = XMVectorZero();*/
	glm::vec4 moveX = glm::vec4(0);
	glm::vec4 moveY = glm::vec4(0);
	glm::vec4 moveZ = glm::vec4(0);
	float moveAmount = 5.0f * deltaTime;

	/*XMVECTOR fwd = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR right = XMVectorSet(1, 0, 0, 0);*/
	glm::vec4 fwd = glm::vec4(0, 0, 1, 0);
	glm::vec4 up = glm::vec4(0, 1, 0, 0);
	glm::vec4 right = glm::vec4(1, 0, 0, 0);

	//XMVECTOR pos = XMLoadFloat3(&(entity->GetPosition()));
	glm::vec4 pos = glm::vec4(entity->GetPosition(),0);

	/*moveX = XMVector3Cross(fwd, up);
	moveY = XMVector3Cross(fwd, right);
	moveZ = XMVector3Cross(up, right);*/
	moveX = glm::vec4(glm::cross(glm::vec3(fwd), glm::vec3( up)),0);
	moveY = glm::vec4(glm::cross(glm::vec3(fwd), glm::vec3(right)), 0);
	moveZ = glm::vec4(glm::cross(glm::vec3(up), glm::vec3(right)), 0);
	moveX = moveX * moveAmount;
	moveY = moveY * moveAmount;
	moveZ = moveZ * moveAmount;
	

	pos += moveX*x + moveY*y + moveZ*z;

	/*XMFLOAT3 position;
	XMStoreFloat3(&position, pos);*/
	glm::vec3 position;
	position = glm::vec3(pos);

	entity->SetPosition(position);
}

// --------------------------------------------------------
//Set the asteroid to active and its lane to move to (1,2,3)
// --------------------------------------------------------
void Asteroid::SetActive(int laneNumber)
{
	collided = false;
	//XMFLOAT3 position;
	glm::vec3 position;
	active = true;

	switch (laneNumber)
	{
	case 1:
	{
		position = glm::vec3(-4.0f, 0.0f, 20.0f);
		entity->SetPosition(position);
		break;
	}
	case 2:
	{
		position = glm::vec3(+0.1f, 0.0f, 20.0f);
		entity->SetPosition(position);
		break;
	}
	default:
		break;
	}
}

// --------------------------------------------------------
//Is the Asteroid active?
// --------------------------------------------------------
bool Asteroid::IsActive()
{
	return active;
}