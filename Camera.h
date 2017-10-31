//Darren Farr
#pragma once

//#include <DirectXMath.h>
#include "glm\glm.hpp"
#include <Windows.h>


class Camera
{
public:
	Camera();
	Camera(unsigned int, unsigned int);
	~Camera();

	void Init();

	void SetWidthHeight(unsigned int, unsigned int);
	void Update(POINT, float);
	void MouseDown(bool);

	void Resize(unsigned int, unsigned int);

	void SetDebugMode(bool);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec4 GetPositon();
	glm::vec4 GetDirection();

/*
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT4 GetPositon();
	DirectX::XMFLOAT4 GetDirection();*/

private:
	/*void CreateMatrices(DirectX::XMFLOAT4, DirectX::XMFLOAT4);

	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 direction;*/

	void CreateMatrices(glm::vec4, glm::vec4);

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec4 position;
	glm::vec4 direction;



	float rotationX;
	float rotationY;

	unsigned int width;
	unsigned int height;

	bool mouseDown;
	bool debugMode;

	POINT lastMouse, mouse;
};