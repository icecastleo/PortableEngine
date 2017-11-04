#pragma once

//#include <DirectXMath.h>
#include "glm\glm.hpp"


struct GlobalLight
{
	//DirectX::XMFLOAT4 AmbientColor;
	glm::vec4 AmbientColor;
};

struct DirectionalLight
{
	//DirectX::XMFLOAT4 DiffuseColor;
	//DirectX::XMFLOAT3 Direction;
	glm::vec4 DiffuseColor;
	glm::vec3 Direction;
};

struct PointLight
{
	/*DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Position;*/
	glm::vec4 DiffuseColor;
	glm::vec3 Position;
};

struct SpotLight
{
	/*DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Position;
	float theta;
	DirectX::XMFLOAT3 Direction;
	float phi;*/
	glm::vec4 DiffuseColor;
	glm::vec3 Position;
	float theta;
	glm::vec3 Direction;
	float phi;
};