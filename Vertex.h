#pragma once

#include "glm\glm.hpp"

struct Vertex
{
	glm::vec3 Position;	    // The position of the vertex
	glm::vec2 UV;			// UV location
	glm::vec3 Normal;		// Normal direction
	glm::vec3 Tangent;		// For normal mapping
};

enum VertexElements
{
	kVertexPosition = 0,
	kVertexUv,
	kVertexNormal,
	kVertexTangent,
	kVertexElemCount
};