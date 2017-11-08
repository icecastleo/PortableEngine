#pragma once

#include "glm\glm.hpp"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init(uint16_t width, uint16_t height);

	glm::vec3 GetPositon();

	void SetPosition(glm::vec3);
	void SetRotation(glm::vec3);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 GetDirection();

	//void Update(POINT, float);
	virtual void Update(float);

	void Resize(uint16_t, uint16_t);

protected:
	void CreateMatrices(uint16_t width, uint16_t height);

	glm::vec3 position;
	glm::vec3 rotation;  // degrees

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 direction;
	glm::vec3 up;

	bool debugMode;

private:
	void MakeViewMatrix();
	void MakeProjectionMatrix(uint16_t width, uint16_t height);
};