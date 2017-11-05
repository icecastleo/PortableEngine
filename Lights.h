#pragma once

//#include <DirectXMath.h>
#include "glm\glm.hpp"


struct GlobalLight
{
	glm::vec4 AmbientColor;
};

struct DirectionalLight
{
	glm::vec4 DiffuseColor;
	glm::vec3 Direction;
};

struct PointLight
{
	glm::vec4 DiffuseColor;
	glm::vec3 Position;
};

struct SpotLight
{
	glm::vec4 DiffuseColor;
	glm::vec3 Position;
	float theta;
	glm::vec3 Direction;
	float phi;
};