#include "Entity.h"

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
Entity::Entity(Mesh* _mesh, D3D11Material* _mat, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale)
{
	mesh = _mesh;
	mat = _mat;
	transform.position = _pos;
	transform.rotation = _rot;
	transform.scale = _scale;
	parent = nullptr;

	XMStoreFloat4x4(&localMat, DirectX::XMMatrixIdentity());
	XMStoreFloat4x4(&worldMat, DirectX::XMMatrixIdentity());

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
	XMMATRIX local = DirectX::XMMatrixMultiply(
		DirectX::XMMatrixMultiply(
			DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z),
			DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z)
		),
		DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z)
	);

	XMStoreFloat4x4(
		&localMat,
		DirectX::XMMatrixTranspose(local)
	);

	if (parent != nullptr) {
		XMMATRIX world = DirectX::XMMatrixMultiply(
			local,
			DirectX::XMMatrixTranspose(
				XMLoadFloat4x4(&parent->GetWorldMat())
			)
		);
		XMStoreFloat4x4(
			&worldMat,
			DirectX::XMMatrixTranspose(world)
		);
	}
	else
	{
		worldMat = localMat;
	}
}

// --------------------------------------------------------
//Set the position of the entity
// --------------------------------------------------------
void Entity::SetPosition(XMFLOAT3 newPos)
{
	transform.position = newPos;
}

// --------------------------------------------------------
//Set the rotation of the entity
// --------------------------------------------------------
void Entity::SetRotation(XMFLOAT3 newRot)
{
	transform.rotation = newRot;
}

// --------------------------------------------------------
//Set the scale of the entity
// --------------------------------------------------------
void Entity::SetScale(XMFLOAT3 newScale)
{
	transform.scale = newScale;
}

// --------------------------------------------------------
//Return the entities world matrix
// --------------------------------------------------------
XMFLOAT4X4 Entity::GetWorldMat()
{
	return worldMat;
}

// --------------------------------------------------------
//Return the entities position
// --------------------------------------------------------
XMFLOAT3 Entity::GetPosition()
{
	return transform.position;
}

// --------------------------------------------------------
//Return the entities rotation
// --------------------------------------------------------
XMFLOAT3 Entity::GetRotation()
{
	return transform.rotation;
}

// --------------------------------------------------------
//Return the entities scale
// --------------------------------------------------------
XMFLOAT3 Entity::GetScale()
{
	return transform.scale;
}

// --------------------------------------------------------
//Return the entities mesh
// --------------------------------------------------------
Mesh* Entity::GetMesh()
{
	return mesh;
}

// --------------------------------------------------------
//Return the entities material
// --------------------------------------------------------
D3D11Material* Entity::GetMat()
{
	return mat;
}