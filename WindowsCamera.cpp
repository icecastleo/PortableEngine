#include "WindowsCamera.h"
#include "glm\gtc\matrix_transform.hpp"

WindowsCamera::WindowsCamera()
{
	
}

WindowsCamera::~WindowsCamera()
{
}

void WindowsCamera::Update(float deltaTime) {
	Camera::Update(deltaTime);

	if (debugMode)
	{
		static float speed = 2.0f;

		glm::vec3 moveDir = glm::vec3(0.0f);

		if (GetKeyState('W') & 0x8000)
		{
			moveDir = direction;
			position += moveDir * speed * deltaTime;
		}
		if (GetKeyState('S') & 0x8000)
		{
			moveDir = -direction;
			position += moveDir * speed * deltaTime;
		}
		if (GetKeyState('A') & 0x8000)
		{
			moveDir = glm::vec4(glm::cross(glm::vec3(direction), glm::vec3(up)), 0.0f);
			position += moveDir * speed * deltaTime;
		}
		if (GetKeyState('D') & 0x8000)
		{
			moveDir = -glm::vec4(glm::cross(glm::vec3(direction), glm::vec3(up)), 0.0f);
			position += moveDir * speed * deltaTime;
		}
		if (GetKeyState('E') & 0x8000)
		{
			moveDir = up;
			position += moveDir * speed * deltaTime;
		}
		if (GetKeyState('Q') & 0x8000)
		{
			moveDir = -up;
			position += moveDir * speed * deltaTime;
		}
	}
}
