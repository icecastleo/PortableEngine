#pragma once
#include <DirectXMath.h>

using namespace DirectX;

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

	bool BoundingSphereCollision(float firstObjBoundingSphere,
		XMMATRIX& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMMATRIX& secondObjWorldSpace);

private:
	Collision();
};

