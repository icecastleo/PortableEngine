#include "Entity.h"
#include "glm\gtc\matrix_transform.hpp"
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
Entity::Entity(D3D11Mesh* _mesh, D3D11Material* _mat, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
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
	/*XMMATRIX local = DirectX::XMMatrixMultiply(
		DirectX::XMMatrixMultiply(
			DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z),
			DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z)
		),
		DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z)
	);

	XMStoreFloat4x4(
		&localMat,
		DirectX::XMMatrixTranspose(local)
	);*/

	glm::mat4 local = glm::mat4(1.0f);
	glm::mat4 myTranslationMatrix = glm::translate(local, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
	glm::mat4 myRotationMatrix = glm::rotate(local, transform.rotation.x, glm::vec3(1, 0, 0));
	myRotationMatrix = glm::rotate(myRotationMatrix, transform.rotation.y, glm::vec3(0, 1, 0));
	myRotationMatrix = glm::rotate(myRotationMatrix, transform.rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 myScaleMatrix = glm::scale(local, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
	local = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	localMat = local;



	if (parent != nullptr) {
		/*XMMATRIX world = DirectX::XMMatrixMultiply(
			local,
			DirectX::XMMatrixTranspose(
				XMLoadFloat4x4(&parent->GetWorldMat())
			)
		);
		XMStoreFloat4x4(
			&worldMat,
			DirectX::XMMatrixTranspose(world)
		);*/


		glm::mat4 world = parent->GetWorldMat() * local;
		worldMat = world;



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
D3D11Mesh* Entity::GetMesh()
{ return mesh; }

// --------------------------------------------------------
//Return the entities material
// --------------------------------------------------------
D3D11Material* Entity::GetMat()
{
	return mat;
}
