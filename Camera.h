#pragma once

#include "glm\glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	void Init(uint16_t width, uint16_t height);

	//void Update(POINT, float);
	virtual void Update(float);

	void Resize(uint16_t, uint16_t);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec4 GetPositon();
	glm::vec4 GetDirection();

	void SetPosition(glm::vec4);
	void SetDir(glm::vec4);

protected:
	void CreateMatrices(glm::vec4, glm::vec4, uint16_t width, uint16_t height);

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec4 position;
	glm::vec4 direction;

	bool debugMode;

	float rotationX;
	float rotationY;
};