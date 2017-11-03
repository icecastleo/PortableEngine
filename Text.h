#pragma once
//#include <DirectXMath.h>
#include "glm\glm.hpp"
struct textObject
{
	const wchar_t* text;
	//DirectX::XMFLOAT2 position;
	glm::vec2 position;
	float xPercent;
	float yPercent;
};