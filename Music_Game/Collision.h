#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	static Collision* Instance();

	Collision();
	~Collision();

	bool BoundingSphereCollision(float firstObjBoundingSphere,
		XMMATRIX& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMMATRIX& secondObjWorldSpace);

private:
	static Collision* m_Instance;
};

