#include "Collision.h"
#include <iostream>

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::BoundingSphereCollision(float firstObjBoundingSphere,
	XMMATRIX& firstObjWorldSpace,
	float secondObjBoundingSphere,
	XMMATRIX& secondObjWorldSpace)
{
	float objectsDistance = 0.0f;

	XMFLOAT4X4 one;
	XMStoreFloat4x4(&(one), firstObjWorldSpace);

	XMFLOAT4X4 two;
	XMStoreFloat4x4(&(two), secondObjWorldSpace);

	objectsDistance = sqrt((one._14 - two._14) * (one._14 - two._14) +
		(one._24 - two._24) * (one._24 - two._24) + 
		(one._34 - two._34) * (one._34 - two._34));


	//If the distance between the two objects is less than the sum of their bounding spheres...
	if (objectsDistance <= (firstObjBoundingSphere + secondObjBoundingSphere))
		return true;

	//If the bounding spheres are not colliding, return false
	return false;
}