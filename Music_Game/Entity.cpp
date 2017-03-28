//Darren Farr
#include "Entity.h"

using namespace DirectX;

// --------------------------------------------------------
//Default Constructor
// --------------------------------------------------------
Entity::Entity() {}

// --------------------------------------------------------
//Default Deconstructor
// --------------------------------------------------------
Entity::~Entity()
{
	//delete mesh;
}

// --------------------------------------------------------
//Override constructor using the Identity Matrix 
//for world matrix
// --------------------------------------------------------
Entity::Entity(Mesh* _mesh, Material* _mat, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale)
{
	XMStoreFloat4x4(&worldMat, XMMatrixIdentity());
	mesh = _mesh;
	mat = _mat;
	transform.position = _pos;
	transform.rotation = _rot;
	transform.scale = _scale;

	SetWorldMat();

	posOrig = transform.position;
	rotOrig = transform.rotation;
	scaleOrig = transform.scale;
}

// --------------------------------------------------------
//Upadte the entity
// --------------------------------------------------------
void Entity::Update()
{
	SetWorldMat();
}


// --------------------------------------------------------
//Set the world matrix for the entity based on its 
//translation(position), rotation, and/or scale
// --------------------------------------------------------
void Entity::SetWorldMat()
{
	XMMATRIX _scale = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	XMVECTOR _rotT = XMLoadFloat3(&(transform.rotation));
	XMMATRIX _rot = XMMatrixRotationRollPitchYawFromVector(_rotT);
	XMMATRIX _trans = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);

	XMMATRIX world = _scale * _rot * _trans;
	XMStoreFloat4x4(&worldMat, XMMatrixTranspose(world));
}

// --------------------------------------------------------
//Set the position of the entity
// --------------------------------------------------------
void Entity::SetPosition(XMFLOAT3 newPos)
{ transform.position = newPos; }

// --------------------------------------------------------
//Set the rotation of the entity
// --------------------------------------------------------
void Entity::SetRotation(XMFLOAT3 newRot)
{ transform.rotation = newRot; }

// --------------------------------------------------------
//Set the scale of the entity
// --------------------------------------------------------
void Entity::SetScale(XMFLOAT3 newScale)
{ transform.scale = newScale; }

// --------------------------------------------------------
//Return the entities world matrix
// --------------------------------------------------------
XMFLOAT4X4 Entity::GetWorldMat()
{ return worldMat; }

// --------------------------------------------------------
//Return the entities position
// --------------------------------------------------------
XMFLOAT3 Entity::GetPosition()
{ return transform.position; }

// --------------------------------------------------------
//Return the entities rotation
// --------------------------------------------------------
XMFLOAT3 Entity::GetRotation()
{ return transform.rotation; }

// --------------------------------------------------------
//Return the entities scale
// --------------------------------------------------------
XMFLOAT3 Entity::GetScale()
{ return transform.scale; }

// --------------------------------------------------------
//Return the entities mesh
// --------------------------------------------------------
Mesh* Entity::GetMesh()
{ return mesh; }

// --------------------------------------------------------
//Return the entities material
// --------------------------------------------------------
Material* Entity::GetMat()
{ return mat; }

// --------------------------------------------------------
//Return the entity back to its original positon, rotation, scale
// --------------------------------------------------------
void Entity::Reset()
{
	transform.position = posOrig;
	transform.rotation = rotOrig;
	transform.scale = scaleOrig;
	Update();
}