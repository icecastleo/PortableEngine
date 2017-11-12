#include "Entity.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\quaternion.hpp"

//using namespace DirectX;
using namespace glm;

Entity::Entity() 
{
}

Entity::~Entity()
{
	if (dirtyUpdate)
		delete dirtyUpdate;
}

Entity::Entity(Mesh* _mesh, Material* _mat, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
	mesh = _mesh;
	mat = _mat;
	transform.position = _pos;
	transform.rotation = _rot;
	transform.scale = _scale;
	parent = nullptr;

	localMat = glm::mat4(1);
	worldMat = glm::mat4(1);
	//SetWorldMat();
}

void Entity::Update(float deltaTime)
{
	if (dirtyUpdate) {
		dirtyUpdate->Update(deltaTime);
	}

	SetWorldMat();
}

void Entity::SetParent(Entity * e)
{
	if (parent != nullptr) {
		for (unsigned i = 0; i < parent->children.size(); i++) {
			if (parent->children[i] == this) {
				parent->children.erase(parent->children.begin() + i);
				break;
			}
		}
	}

	parent = e;
	e->children.push_back(this);
}

// --------------------------------------------------------
//Set the world matrix for the entity based on its 
//translation(position), rotation, and/or scale
// --------------------------------------------------------
void Entity::SetWorldMat()
{
	mat4 local = mat4(1.0f);
	mat4 myTranslationMatrix = translate(local, transform.position);
	mat4 myRotationMatrix = toMat4(quat(vec3(radians(transform.rotation))));
	mat4 myScaleMatrix = scale(local, transform.scale);
	local = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	localMat = transpose(local);

	if (parent != nullptr) {
		mat4 world =  transpose(parent->GetWorldMat()) * local ;	
		worldMat = transpose(world);
	}
	else
	{
		worldMat = localMat;
	}
}

void Entity::SetPosition(glm::vec3 newPos)
{
	transform.position = newPos;
}

void Entity::SetRotation(glm::vec3 newRot)
{
	transform.rotation = newRot;
}

void Entity::SetScale(glm::vec3 newScale)
{
	transform.scale = newScale;
}

glm::mat4 Entity::GetWorldMat()
{
	return worldMat;
}

glm::vec3 Entity::GetPosition()
{
	return transform.position;
}

glm::vec3 Entity::GetRotation()
{
	return transform.rotation;
}

glm::vec3 Entity::GetScale()
{
	return transform.scale;
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

Material* Entity::GetMat()
{
	return mat;
}
