#include "Collision.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool BoundingSphereCollision(float firstObjBoundingSphere,
	XMVECTOR firstObjCenterOffset,
	XMMATRIX& firstObjWorldSpace,
	float secondObjBoundingSphere,
	XMVECTOR secondObjCenterOffset,
	XMMATRIX& secondObjWorldSpace)
{
	//Declare local variables
	XMVECTOR world_1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR world_2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	float objectsDistance = 0.0f;

	//Transform the objects world space to objects REAL center in world space
	world_1 = XMVector3TransformCoord(firstObjCenterOffset, firstObjWorldSpace);
	world_2 = XMVector3TransformCoord(secondObjCenterOffset, secondObjWorldSpace);

	//Get the distance between the two objects
	objectsDistance = XMVectorGetX(XMVector3Length(world_1 - world_2));

	//If the distance between the two objects is less than the sum of their bounding spheres...
	if (objectsDistance <= (firstObjBoundingSphere + secondObjBoundingSphere))
		//Return true
		return true;

	//If the bounding spheres are not colliding, return false
	return false;
}

bool BoundingBoxCollision(XMVECTOR& firstObjBoundingBoxMinVertex,
	XMVECTOR& firstObjBoundingBoxMaxVertex,
	XMVECTOR& secondObjBoundingBoxMinVertex,
	XMVECTOR& secondObjBoundingBoxMaxVertex)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if (XMVectorGetX(firstObjBoundingBoxMaxVertex) > XMVectorGetX(secondObjBoundingBoxMinVertex))

		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
		if (XMVectorGetX(firstObjBoundingBoxMinVertex) < XMVectorGetX(secondObjBoundingBoxMaxVertex))

			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
			if (XMVectorGetY(firstObjBoundingBoxMaxVertex) > XMVectorGetY(secondObjBoundingBoxMinVertex))

				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
				if (XMVectorGetY(firstObjBoundingBoxMinVertex) < XMVectorGetY(secondObjBoundingBoxMaxVertex))

					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
					if (XMVectorGetZ(firstObjBoundingBoxMaxVertex) > XMVectorGetZ(secondObjBoundingBoxMinVertex))

						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
						if (XMVectorGetZ(firstObjBoundingBoxMinVertex) < XMVectorGetZ(secondObjBoundingBoxMaxVertex))

							//If we've made it this far, then the two bounding boxes are colliding
							return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}