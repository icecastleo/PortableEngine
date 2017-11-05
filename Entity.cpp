#include "Entity.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\euler_angles.hpp"
using namespace DirectX;

// --------------------------------------------------------
//Default Constructor
// --------------------------------------------------------
Entity::Entity() 
{
}

// --------------------------------------------------------
//Default Deconstructor
// --------------------------------------------------------
Entity::~Entity()
{
	if (dirtyUpdate)
		delete dirtyUpdate;
}

// --------------------------------------------------------
//Override constructor using the Identity Matrix 
//for world matrix
// --------------------------------------------------------
Entity::Entity(Mesh* _mesh, D3D11Material* _mat, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
	mesh = _mesh;
	mat = _mat;
	transform.position = _pos;
	transform.rotation = _rot;
	transform.scale = _scale;
	parent = nullptr;

	//XMStoreFloat4x4(&localMat, DirectX::XMMatrixIdentity());
	//XMStoreFloat4x4(&worldMat, DirectX::XMMatrixIdentity());

	localMat = glm::mat4(1);
	worldMat = glm::mat4(1);
	//SetWorldMat();
}

// --------------------------------------------------------
//Upadte the entity
// --------------------------------------------------------
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

	glm::mat4 local = glm::mat4(1.0f);
	glm::mat4 myTranslationMatrix = glm::translate(local, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
	glm::mat4 myRotationMatrix = glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);
	glm::mat4 myScaleMatrix = glm::scale(local, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
	local = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	localMat = glm::transpose(local);


	if (parent != nullptr) {
		

		glm::mat4 world =  glm::transpose(parent->GetWorldMat()) * local ;
		
		worldMat = glm::transpose(world);



	}
	else
	{
		worldMat = localMat;
	}
}

// --------------------------------------------------------
//Set the position of the entity
// --------------------------------------------------------
void Entity::SetPosition(glm::vec3 newPos)
{
	transform.position = newPos;
}

// --------------------------------------------------------
//Set the rotation of the entity
// --------------------------------------------------------
void Entity::SetRotation(glm::vec3 newRot)
{
	transform.rotation = newRot;
}

// --------------------------------------------------------
//Set the scale of the entity
// --------------------------------------------------------
void Entity::SetScale(glm::vec3 newScale)
{
	transform.scale = newScale;
}

// --------------------------------------------------------
//Return the entities world matrix
// --------------------------------------------------------
glm::mat4 Entity::GetWorldMat()
{
	return worldMat;
}

// --------------------------------------------------------
//Return the entities position
// --------------------------------------------------------
glm::vec3 Entity::GetPosition()
{
	return transform.position;
}

// --------------------------------------------------------
//Return the entities rotation
// --------------------------------------------------------
glm::vec3 Entity::GetRotation()
{
	return transform.rotation;
}

// --------------------------------------------------------
//Return the entities scale
// --------------------------------------------------------
glm::vec3 Entity::GetScale()
{
	return transform.scale;
}

// --------------------------------------------------------
//Return the entities mesh
// --------------------------------------------------------
Mesh* Entity::GetMesh()
{ return mesh; }

// --------------------------------------------------------
//Return the entities material
// --------------------------------------------------------
D3D11Material* Entity::GetMat()
{
	return mat;
}
