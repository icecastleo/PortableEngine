#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	Collision();
	~Collision();

	bool BoundingSphereCollision(float firstObjBoundingSphere,
		XMVECTOR firstObjCenterOffset,
		XMMATRIX& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMVECTOR secondObjCenterOffset,
		XMMATRIX& secondObjWorldSpace);
};

