#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	Collision();
	~Collision();

	bool BoundingSphereCollision(float firstObjBoundingSphere,
		XMMATRIX& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMMATRIX& secondObjWorldSpace);
};

