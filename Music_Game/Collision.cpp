#include "Collision.h"

Collision::Collision()
{
}

bool Collision::BoundingSphereCollision(float firstObjBoundingSphere,
	XMFLOAT4X4& firstObjWorldSpace,
	float secondObjBoundingSphere,
	XMFLOAT4X4& secondObjWorldSpace)
{
	float objectsDistance = 0.0f;

	objectsDistance = sqrt((firstObjWorldSpace._14 - secondObjWorldSpace._14) * (firstObjWorldSpace._14 - secondObjWorldSpace._14) +
		(firstObjWorldSpace._24 - secondObjWorldSpace._24) * (firstObjWorldSpace._24 - secondObjWorldSpace._24) +
		(firstObjWorldSpace._34 - secondObjWorldSpace._34) * (firstObjWorldSpace._34 - secondObjWorldSpace._34));


	//If the distance between the two objects is less than the sum of their bounding spheres...
	if (objectsDistance <= (firstObjBoundingSphere + secondObjBoundingSphere))
		return true;

	//If the bounding spheres are not colliding, return false
	return false;
}