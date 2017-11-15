#include "WindowsCamera.h"
#include "glm\gtc\matrix_transform.hpp"

WindowsCamera::WindowsCamera(uint16_t width, uint16_t height)
	:Camera(width, height)
{
	
}

WindowsCamera::~WindowsCamera()
{
}

void WindowsCamera::Update(float deltaTime) {
	Camera::Update(deltaTime);

	if (debugMode)
	{
		static float speed = 5.0f;

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

		if (GetKeyState('I') & 0x8000)
		{
			rotation += glm::vec3(1.f,0.f,0.f) * speed * 5.f * deltaTime;
		}
		if (GetKeyState('K') & 0x8000)
		{
			rotation += glm::vec3(-1.f, 0.f, 0.f) * speed * 5.f * deltaTime;
		}
		if (GetKeyState('J') & 0x8000)
		{
			rotation += glm::vec3(0.f, 1.f, 0.f) * speed * 5.f * deltaTime;
		}
		if (GetKeyState('L') & 0x8000)
		{
			rotation += glm::vec3(0.f, -1.f, 0.f) * speed * 5.f * deltaTime;
		}
	}
}
