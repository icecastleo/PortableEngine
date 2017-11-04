#pragma once

///#include <DirectXMath.h>
#include "glm\glm.hpp"

//struct Transform
//{
//	DirectX::XMFLOAT3 position;
//	DirectX::XMFLOAT3 rotation;
//	DirectX::XMFLOAT3 scale;
//};

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};