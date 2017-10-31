#pragma once

#include <d3d11.h>
//#include <DirectXMath.h>
#include <vector>
#include "Vertex.h"
#include "D3D11Mesh.h"

using namespace DirectX;

class Collider
{
public:
	Collider();
	Collider(D3D11Mesh*);
	~Collider();

	float GetBoudingSphere();

private:
	//D3D11Mesh* mesh;

	float boundingSphere;

	void CreateBoundingVolumes(std::vector<Vertex> &vertPosArray,    // The array containing our models vertex positions
		float &boundingSphere);                                    // A vector containing the distance between the models actual center and (0, 0, 0) in model space
};

