#pragma once
//#include <DirectXMath.h>
#include "glm\glm.hpp"

//using namespace DirectX;

class Collision
{
public:
	static Collision& Instance()
	{
		static Collision m_Instance;
		return m_Instance;
	}
	// Singleton destructors
	Collision(Collision const&) = delete;

	/*bool Collision::BoundingSphereCollision(float firstObjBoundingSphere,
		XMFLOAT4X4& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMFLOAT4X4& secondObjWorldSpace);*/

	bool Collision::BoundingSphereCollision(float firstObjBoundingSphere,
		glm::mat4& firstObjWorldSpace,
		float secondObjBoundingSphere,
		glm::mat4& secondObjWorldSpace);

private:
	Collision();
};

