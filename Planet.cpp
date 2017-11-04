#include "Planet.h"



Planet::Planet(Entity *entity, float rotation)
{
	this->entity = entity;
	this->rotation = rotation;
}

Planet::~Planet()
{
}

void Planet::Update(float deltaTime)
{
	//entity->SetRotation(DirectX::XMFLOAT3(entity->GetRotation().x, entity->GetRotation().y + rotation, entity->GetRotation().z));
	entity->SetRotation(glm::vec3(entity->GetRotation().x, entity->GetRotation().y + rotation, entity->GetRotation().z));
}
