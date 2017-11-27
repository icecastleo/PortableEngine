#pragma once

#include "Material.h"
#include "Mesh.h"
#include <vector>
#include "Transform.h"


//Entity Class
//An object to hold mesh(s) and local properties
class Entity
{
public:
	Entity();
	virtual ~Entity();
	
	Entity(Mesh*, Material*, glm::vec3, glm::vec3, glm::vec3);

	virtual void Update(float deltaTime);

	glm::mat4 GetWorldMat();
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void SetPosition(glm::vec3);
	void SetRotation(glm::vec3);
	void SetScale(glm::vec3);

	Mesh* GetMesh();
	Material* GetMat();

	Entity* parent;
	std::vector<Entity*> children;

	void SetParent(Entity* e);

	Entity *dirtyUpdate = nullptr;

private:
	void SetWorldMat();
	
	Mesh* mesh;
	Material* mat;

	Transform transform;
	
	glm::mat4 worldMat;
	glm::mat4 localMat;
};
