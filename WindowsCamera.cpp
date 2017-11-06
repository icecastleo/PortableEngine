#include "WindowsCamera.h"
#include "glm\gtc\matrix_transform.hpp"

WindowsCamera::WindowsCamera()
{
	
}

WindowsCamera::~WindowsCamera()
{
}

void WindowsCamera::Update(float deltaTime) {

	glm::vec4 pos = position;
	glm::vec4 up = glm::vec4(0, 1, 0, 0);
	glm::vec4 dir = direction;

	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 _trans = glm::translate(identity, glm::vec3(position.x, position.y, position.z));
	glm::mat4 _rotX = glm::rotate(_trans, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 _rotY = glm::rotate(_rotX, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot = _rotY;
	glm::vec4 fwd = dir;
	fwd = rot * fwd;

	glm::mat4 V = glm::lookAtLH(glm::vec3(pos), glm::vec3(pos + fwd), glm::vec3(rot * up));
	viewMatrix = glm::transpose(V);

	if (debugMode)
	{
		glm::vec4 moveDir = glm::vec4(0.0f);

		float moveAmount = 0.7f * deltaTime;
		if (GetAsyncKeyState('W') & 0x8000)
		{
			moveDir = fwd;
			moveDir = moveDir * moveAmount;
			pos += moveDir;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			moveDir = fwd;
			moveDir = moveDir * moveAmount;
			pos -= moveDir;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			moveDir = glm::vec4(glm::cross(glm::vec3(fwd), glm::vec3(up)), 0.0f);
			moveDir = moveDir * moveAmount;
			pos += moveDir;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			moveDir = glm::vec4(glm::cross(glm::vec3(fwd), glm::vec3(up)), 0.0f);
			moveDir = moveDir * moveAmount;
			pos -= moveDir;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//moveDir = XMVectorSet(0, 1, 0, 0);
			moveDir = glm::vec4(0, 1, 0, 0);
			moveDir = moveDir * moveAmount;
			pos += moveDir;
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			//moveDir = XMVectorSet(0, 1, 0, 0);
			moveDir = glm::vec4(0, 1, 0, 0);
			moveDir = moveDir * moveAmount;
			pos -= moveDir;
		}

		//XMStoreFloat4(&position, pos);
		position = pos;
	}
}
