//Darren Farr
#pragma once

#include <DirectXMath.h>
#include "D3D11Mesh.h"
#include "D3D11Material.h"
#include <vector>
#include "Transform.h"


//Entity Class
//An object to hold mesh(s) and local properties
class Entity
{
public:
	Entity();
	virtual ~Entity();
	Entity(D3D11Mesh*, D3D11Material*, DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);

	virtual void Update(float deltaTime);

	DirectX::XMFLOAT4X4 GetWorldMat();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	void SetPosition(DirectX::XMFLOAT3);
	void SetRotation(DirectX::XMFLOAT3);
	void SetScale(DirectX::XMFLOAT3);

	D3D11Mesh* GetMesh();
	D3D11Material* GetMat();

	Entity* parent;
	std::vector<Entity*> children;

	void SetParent(Entity* e);

	Entity *dirtyUpdate;

private:
	void SetWorldMat();
	
	D3D11Mesh* mesh;
	D3D11Material* mat;

	Transform transform;
	DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMFLOAT4X4 localMat;
};
