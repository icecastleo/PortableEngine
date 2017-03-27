#pragma once

#include <DirectXMath.h>


struct GlobalLight
{
	DirectX::XMFLOAT4 AmbientColor;
};

struct DirectionalLight
{
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Direction;
};

struct PointLight
{
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Position;
};

struct SpotLight
{
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Position;
	float theta;
	DirectX::XMFLOAT3 Direction;
	float phi;
};