#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "Vertex.h"
#include "Mesh.h"

using namespace DirectX;

class Collider
{
public:
	Collider();
	Collider(Mesh*);
	~Collider();

	float GetBoudingSphere();
	XMFLOAT3 GetObjectCenterOffset();

	void GetVolume();

private:
	Mesh* mesh;

	std::vector<XMFLOAT3> boundingBoxVerts;
	std::vector<DWORD> boundingBoxIndex;
	float boundingSphere;
	XMFLOAT3 objectCenterOffsetFloat;

	void CreateBoundingVolumes(std::vector<Vertex> &vertPosArray,    // The array containing our models vertex positions
		std::vector<XMFLOAT3>& boundingBoxVerts,                            // Array we want to store the bounding box's vertex positions
		std::vector<DWORD>& boundingBoxIndex,                            // This is our bounding box's index array
		float &boundingSphere,                                            // The float containing the radius of our bounding sphere
		XMVECTOR &objectCenterOffset);                                    // A vector containing the distance between the models actual center and (0, 0, 0) in model space
};

