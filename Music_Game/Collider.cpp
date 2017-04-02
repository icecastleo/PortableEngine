#include "Collider.h"
#include <iostream>

Collider::Collider()
{
	
}

Collider::Collider(Mesh* _mesh) : mesh(_mesh)
{
	boundingSphere = 0.0f;

	GetVolume();
}

Collider::~Collider()
{
}

void Collider::GetVolume()
{
	std::vector<Vertex> meshVertexCollection = mesh->GetVertexCollection();

	XMVECTOR centerOffsetVector = XMLoadFloat3(&(objectCenterOffsetFloat));

	CreateBoundingVolumes(meshVertexCollection, boundingBoxVerts, boundingBoxIndex, boundingSphere, centerOffsetVector);
}

void Collider::CreateBoundingVolumes(std::vector<Vertex> &vertPosArray,
	std::vector<XMFLOAT3>& boundingBoxVerts,
	std::vector<DWORD>& boundingBoxIndex,
	float &boundingSphere,
	XMVECTOR &objectCenterOffset)
{
	XMFLOAT3 minVertex = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVertex = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (UINT i = 0; i < vertPosArray.size(); i++)
	{
		// The minVertex and maxVertex will most likely not be actual vertices in the model, but vertices
		// that use the smallest and largest x, y, and z values from the model to be sure ALL vertices are
		// covered by the bounding volume

		//Get the smallest vertex 
		minVertex.x = min(minVertex.x, vertPosArray[i].Position.x);    // Find smallest x value in model
		minVertex.y = min(minVertex.y, vertPosArray[i].Position.y);    // Find smallest y value in model
		minVertex.z = min(minVertex.z, vertPosArray[i].Position.z);    // Find smallest z value in model

																	   //Get the largest vertex 
		maxVertex.x = max(maxVertex.x, vertPosArray[i].Position.x);    // Find largest x value in model
		maxVertex.y = max(maxVertex.y, vertPosArray[i].Position.y);    // Find largest y value in model
		maxVertex.z = max(maxVertex.z, vertPosArray[i].Position.z);    // Find largest z value in model
	}

	// Compute distance between maxVertex and minVertex
	float distX = (maxVertex.x - minVertex.x) / 2.0f;
	float distY = (maxVertex.y - minVertex.y) / 2.0f;
	float distZ = (maxVertex.z - minVertex.z) / 2.0f;

	// Now store the distance between (0, 0, 0) in model space to the models real center
	objectCenterOffset = XMVectorSet(maxVertex.x - distX, maxVertex.y - distY, maxVertex.z - distZ, 0.0f);

	// Compute bounding sphere (distance between min and max bounding box vertices)
	// boundingSphere = sqrt(distX*distX + distY*distY + distZ*distZ) / 2.0f;
	boundingSphere = XMVectorGetX(XMVector3Length(XMVectorSet(distX, distY, distZ, 0.0f)));

	// Create bounding box    
	// Front Vertices
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, minVertex.z));

	// Back Vertices
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, maxVertex.z));

	DWORD* i = new DWORD[36];

	// Front Face
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Back Face
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Top Face
	i[12] = 1; i[13] = 7; i[14] = 6;
	i[15] = 1; i[16] = 6; i[17] = 2;

	// Bottom Face
	i[18] = 0; i[19] = 4; i[20] = 5;
	i[21] = 0; i[22] = 5; i[23] = 3;

	// Left Face
	i[24] = 4; i[25] = 7; i[26] = 1;
	i[27] = 4; i[28] = 1; i[29] = 0;

	// Right Face
	i[30] = 3; i[31] = 2; i[32] = 6;
	i[33] = 3; i[34] = 6; i[35] = 5;

	for (int j = 0; j < 36; j++)
		boundingBoxIndex.push_back(i[j]);

	XMStoreFloat3(&(objectCenterOffsetFloat), objectCenterOffset);
}

float Collider::GetBoudingSphere()
{
	return boundingSphere;
}

XMFLOAT3 Collider::GetObjectCenterOffset()
{
	return objectCenterOffsetFloat;
}