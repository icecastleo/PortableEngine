//Darren Farr
#pragma once

#include <DirectXMath.h>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

//Entity Class
//An object to hold mesh(s) and local properties
class Entity
{
public:
	Entity();
	~Entity();
	Entity(Mesh*, Material*, DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);

	void Update();

	DirectX::XMFLOAT4X4 GetWorldMat();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	void SetPosition(DirectX::XMFLOAT3);
	void SetRotation(DirectX::XMFLOAT3);
	void SetScale(DirectX::XMFLOAT3);
	void Reset();

	Mesh* GetMesh();
	Material* GetMat();

	Entity* parent;
	Entity* child;

	void SetParent(Entity* e);

private:

	void SetWorldMat();
	
	Mesh* mesh;
	Material* mat;



	DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMFLOAT4X4 localMat;
	Transform transform;
	/*DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 rot;
	DirectX::XMFLOAT3 scale;*/
	DirectX::XMFLOAT3 posOrig;
	DirectX::XMFLOAT3 rotOrig;
	DirectX::XMFLOAT3 scaleOrig;
};