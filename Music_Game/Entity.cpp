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
	pos = _pos;
	rot = _rot;
	scale = _scale;

	SetWorldMat();

	posOrig = pos;
	rotOrig = rot;
	scaleOrig = scale;
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
	XMMATRIX _scale = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMVECTOR _rotT = XMLoadFloat3(&rot);
	XMMATRIX _rot = XMMatrixRotationRollPitchYawFromVector(_rotT);
	XMMATRIX _trans = XMMatrixTranslation(pos.x, pos.y, pos.z);

	XMMATRIX world = _scale * _rot * _trans;
	XMStoreFloat4x4(&worldMat, XMMatrixTranspose(world));
}

// --------------------------------------------------------
//Set the position of the entity
// --------------------------------------------------------
void Entity::SetPosition(XMFLOAT3 newPos)
{ pos = newPos; }

// --------------------------------------------------------
//Set the rotation of the entity
// --------------------------------------------------------
void Entity::SetRotation(XMFLOAT3 newRot)
{ rot = newRot; }

// --------------------------------------------------------
//Set the scale of the entity
// --------------------------------------------------------
void Entity::SetScale(XMFLOAT3 newScale)
{ scale = newScale; }

// --------------------------------------------------------
//Return the entities world matrix
// --------------------------------------------------------
XMFLOAT4X4 Entity::GetWorldMat()
{ return worldMat; }

// --------------------------------------------------------
//Return the entities position
// --------------------------------------------------------
XMFLOAT3 Entity::GetPosition()
{ return pos; }

// --------------------------------------------------------
//Return the entities rotation
// --------------------------------------------------------
XMFLOAT3 Entity::GetRotation()
{ return rot; }

// --------------------------------------------------------
//Return the entities scale
// --------------------------------------------------------
XMFLOAT3 Entity::GetScale()
{ return scale; }

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
	pos = posOrig;
	rot = rotOrig;
	scale = scaleOrig;
	Update();
}