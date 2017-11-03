//Darren Farr
#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

//using namespace DirectX;

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Camera::Camera() 
{
	width = 0;
	height = 0;
	mouseDown = false;
	debugMode = false;
}

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Camera::Camera(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
	mouseDown = false;
	debugMode = false;
}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
Camera::~Camera() {}

//Set the width and height

void Camera::SetWidthHeight(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
}

void Camera::Init()
{
	//position = XMFLOAT4(0, 0, -5, 0);
	//position = XMFLOAT4(0, 8, -15, 0);
	//direction = XMFLOAT4(0, -0.3f, 1, 0);

	position = glm::vec4(0, 8, -15, 0);
	direction = glm::vec4(0, -0.3f, 1, 0);

	rotationX = 0.0f;
	rotationY = 100.0f;
	CreateMatrices(position, direction);
	lastMouse.x = 0;
	lastMouse.y = 0;
}

//---------------------------------------------------------
//Create the base matrices for the camera
//Base code from Game.cpp - Chris Cascioli
//---------------------------------------------------------
void Camera::CreateMatrices(glm::vec4 position, glm::vec4 direction)
{
	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	//XMVECTOR pos = XMLoadFloat4(&position);
	//XMVECTOR dir = XMLoadFloat4(&direction);
	//XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	//XMMATRIX V = XMMatrixLookToLH(
	//	pos,     // The position of the "camera"
	//	dir,     // Direction the camera is looking
	//	up);     // "Up" direction in 3D space (prevents roll)
	//XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	//// Create the Projection matrix
	//// - This should match the window's aspect ratio, and also update anytime
	////   the window resizes (which is already happening in OnResize() below)
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,		// Field of View Angle
	//	(float)width / height,		// Aspect ratio
	//	0.1f,						// Near clip plane distance
	//	100.0f);					// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!



	glm::vec4 pos = position;
	glm::vec4 dir = direction;
	glm::vec4 up = glm::vec4(0, 1, 0, 0);

	glm::mat4 V = glm::lookAtLH(glm::vec3(pos), glm::vec3(dir), glm::vec3(up));
	viewMatrix = V;

	float FoV = 0.25f * 3.1415926535f;
	glm::mat4 P = glm::perspectiveLH(glm::radians(FoV), (float)width / height, 0.1f, 100.0f);

	projectionMatrix = P;

}

//---------------------------------------------------------
//
//---------------------------------------------------------
void Camera::MouseDown(bool down)
{ mouseDown = down; }

//---------------------------------------------------------
//Camera Update, checks for commands to move camera
//---------------------------------------------------------
void Camera::Update(POINT mouse, float deltaTime)
{
	if (debugMode)
	{
		/*XMFLOAT3 temp;
		XMVECTOR pos = XMLoadFloat4(&position);
		XMVECTOR up = XMVectorSet(0, 1, 0, 0);
*/
		glm::vec3 temp;
		glm::vec4 pos = position;
		glm::vec4 up = glm::vec4(0, 1, 0, 0);



		float move;

		if (mouseDown)
		{
			float x = lastMouse.x - mouse.x;
			float y = lastMouse.y - mouse.y;

			//rotationY -= x / 100;
			//rotationX += y / 100;
			lastMouse = mouse;

			if (x < 20 && x > -20)
			{
				rotationY -= x / 100;
			}
			if (y < 20 && y > -20)
			{
				rotationX -= y / 100;
			}

		}

		////XMMATRIX _rotX = XMMatrixRotationX(rotationX);
		//XMMATRIX _rotY = XMMatrixRotationY(rotationY);
		////XMMATRIX _trans = XMMatrixTranslation(position.x, position.y, position.z);
		//XMMATRIX rot = _rotX  * _rotY;
		//XMVECTOR fwd = XMVectorSet(0, 0, 1, 0);

		//fwd = XMVector3Transform(fwd, rot);

		//XMStoreFloat4(&direction, fwd);

		glm::mat4 identity = glm::mat4(1.0f);
		glm::mat4 _trans = glm::translate(identity, glm::vec3(position.x, position.y, position.z));
		glm::mat4 _rotX = glm::rotate(_trans, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 _rotY = glm::rotate(_rotX, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rot =  _rotY;
		glm::vec4 fwd = glm::vec4(0, 0, 1, 0);
		fwd = rot * fwd;


		//XMMATRIX V = XMMatrixLookToLH(
		//	pos,     // The position of the "camera"
		//	fwd,     // Direction the camera is looking
		//	up);     // "Up" direction in 3D space (prevents roll)
		//XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

		glm::mat4 V = glm::lookAtLH(glm::vec3(pos), glm::vec3(fwd), glm::vec3(up));
		viewMatrix = V;

		//XMVECTOR moveDir = XMVectorZero();

		glm::vec4 moveDir = glm::vec4(0.0f);

		float moveAmount = 0.7f * deltaTime;
		if (GetAsyncKeyState('W') & 0x8000)
		{
			//moveDir = XMVectorSet(0, 0, 1, 0);
			//moveDir = XMVector3Transform(moveDir, rot);

			moveDir = glm::vec4(0, 0, 1, 0);
			moveDir = rot * moveDir;

			moveDir = moveDir * moveAmount;
			pos += moveDir;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			//moveDir = XMVectorSet(0, 0, 1, 0);
			//moveDir = XMVector3Transform(moveDir, rot);

			moveDir = glm::vec4(0, 0, 1, 0);
			moveDir = rot * moveDir;

			moveDir = moveDir * moveAmount;
			pos -= moveDir;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			//moveDir = XMVector3Cross(fwd, up);
			moveDir = glm::vec4(glm::cross(glm::vec3(fwd), glm::vec3(up)), 0.0f);
			moveDir = moveDir * moveAmount;
			pos += moveDir;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			//moveDir = XMVector3Cross(fwd, up);
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

//---------------------------------------------------------
//Return the view matrix
//---------------------------------------------------------
glm::mat4 Camera::GetViewMatrix()
{ return viewMatrix; }

//---------------------------------------------------------
//Return the projection matrix
//---------------------------------------------------------
glm::mat4 Camera::GetProjectionMatrix()
{ return projectionMatrix; }

//---------------------------------------------------------
//Return the Position
//---------------------------------------------------------
glm::vec4 Camera::GetPositon()
{ return position; }

//---------------------------------------------------------
//Return the Direction
//---------------------------------------------------------
glm::vec4 Camera::GetDirection()
{ return direction; }

//---------------------------------------------------------
//Resize the Screen
//---------------------------------------------------------
void Camera::Resize(unsigned int width, unsigned int height)
{

	// Update our projection matrix since the window size changed
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	float FoV = 0.25f * 3.1415926535f;
	glm::mat4 P = glm::perspectiveLH(glm::radians(FoV), (float)width / height, 0.1f, 100.0f);

	projectionMatrix = P;

}

//---------------------------------------------------------
//Toggle Camera debug mode
//---------------------------------------------------------
void Camera::SetDebugMode(bool mode)
{
	debugMode = mode;
}