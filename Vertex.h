#pragma once

//#include <DirectXMath.h>

#include "glm\glm.hpp"

// --------------------------------------------------------
// A custom vertex definition
//
// You will eventually ADD TO this, and/or make more of these!
// --------------------------------------------------------
//struct Vertex
//{
//	DirectX::XMFLOAT3 Position;	    // The position of the vertex
//	DirectX::XMFLOAT2 UV;			// UV location
//	DirectX::XMFLOAT3 Normal;		// Normal direction
//	DirectX::XMFLOAT3 Tangent;		// For normal mapping
//};

struct Vertex
{
	glm::vec3 Position;	    // The position of the vertex
	glm::vec2 UV;			// UV location
	glm::vec3 Normal;		// Normal direction
	glm::vec3 Tangent;		// For normal mapping
};