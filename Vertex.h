#pragma once

#include "glm\glm.hpp"

struct Vertex
{
	glm::vec3 Position;	    // The position of the vertex
	//float padding;
	glm::vec2 UV;			// UV location
	//glm::vec2 padding2;
	glm::vec3 Normal;		// Normal direction
	//float padding3;
	glm::vec3 Tangent;		// For normal mapping
	//float padding4;
};