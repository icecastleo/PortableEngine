//Darren Farr
#include "Camera.h"
#include <iostream>

using namespace DirectX;

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Camera::Camera() 
{
	width = 0;
	height = 0;
}

//---------------------------------------------------------
//Default Constructor
//---------------------------------------------------------
Camera::Camera(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
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
	position = XMFLOAT4(0, 8, -15, 0);
	direction = XMFLOAT4(0, -0.3f, 1, 0);
	CreateMatrices(position, direction);
}

//---------------------------------------------------------
//Create the base matrices for the camera
//Base code from Game.cpp - Chris Cascioli
//---------------------------------------------------------
void Camera::CreateMatrices(XMFLOAT4 position, XMFLOAT4 direction)
{
	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMLoadFloat4(&position);
	XMVECTOR dir = XMLoadFloat4(&direction);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//   the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
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
{}

//---------------------------------------------------------
//Return the view matrix
//---------------------------------------------------------
XMFLOAT4X4 Camera::GetViewMatrix()
{ return viewMatrix; }

//---------------------------------------------------------
//Return the projection matrix
//---------------------------------------------------------
XMFLOAT4X4 Camera::GetProjectionMatrix()
{ return projectionMatrix; }

//---------------------------------------------------------
//Return the Position
//---------------------------------------------------------
XMFLOAT4 Camera::GetPositon()
{ return position; }

//---------------------------------------------------------
//Return the Direction
//---------------------------------------------------------
DirectX::XMFLOAT4 Camera::GetDirection()
{ return direction; }

//---------------------------------------------------------
//Resize the Screen
//---------------------------------------------------------
void Camera::Resize(unsigned int width, unsigned int height)
{

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}