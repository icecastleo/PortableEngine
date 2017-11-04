//Darren Farr
#pragma once

//#include <DirectXMath.h>
#include "Mesh.h"
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
	//Entity(D3D11Mesh*, D3D11Material*, DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);
	Entity(Mesh*, D3D11Material*, glm::vec3, glm::vec3, glm::vec3);

	virtual void Update(float deltaTime);

	/*DirectX::XMFLOAT4X4 GetWorldMat();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();*/
	glm::mat4 GetWorldMat();
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	/*void SetPosition(DirectX::XMFLOAT3);
	void SetRotation(DirectX::XMFLOAT3);
	void SetScale(DirectX::XMFLOAT3);*/
	void SetPosition(glm::vec3);
	void SetRotation(glm::vec3);
	void SetScale(glm::vec3);

	Mesh* GetMesh();
	D3D11Material* GetMat();

	Entity* parent;
	std::vector<Entity*> children;

	void SetParent(Entity* e);

	Entity *dirtyUpdate = nullptr;

private:
	void SetWorldMat();
	
	Mesh* mesh;
	D3D11Material* mat;

	Transform transform;
	/*DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMFLOAT4X4 localMat;*/
	glm::mat4 worldMat;
	glm::mat4 localMat;
};
