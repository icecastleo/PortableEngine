#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"

Camera::Camera()
{

#if defined(DEBUG) | defined(_DEBUG)
	debugMode = true;
#endif // DEBUG

}

Camera::~Camera() 
{
}

void Camera::SetPosition(glm::vec4 pos) {
	position = pos;
}

void Camera::SetDir(glm::vec4 dir) {
	direction = dir;
}
void Camera::Init(uint16_t width, uint16_t height)
{
	// FIXME:  
#if _PC
	position = glm::vec4(0, 8, -15, 0);
	direction = glm::vec4(0, -0.3f, 1, 0);
#endif	
#if _PS4
	position = glm::vec4(5.0f, 10.0f, 20.0f, 0);
	direction = glm::vec4(-5.0f, -10.0f, -20.0f, 0);
#endif

	rotationX = 0.0f;
	rotationY = 0.0f;
	CreateMatrices(position, direction, width, height);
}

// Create the base matrices for the camera
void Camera::CreateMatrices(glm::vec4 position, glm::vec4 direction, uint16_t width, uint16_t height)
{
	glm::vec4 pos = position;
	glm::vec4 dir = direction;
	glm::vec4 up = glm::vec4(0, 1, 0, 0);
	glm::mat4 V = glm::lookAtLH(glm::vec3(pos), glm::vec3(dir+pos), glm::vec3(up));
	viewMatrix = glm::transpose(V);

	float FoV = 0.25f * 3.1415926535f;
	glm::mat4 P = glm::perspectiveFovLH(FoV, (float)width ,(float)height, 0.1f, 100.0f);
	projectionMatrix = glm::transpose(P);
}

void Camera::Update(float deltaTime) 
{
	
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

glm::vec4 Camera::GetPositon()
{
	return position;
}

glm::vec4 Camera::GetDirection()
{
	return direction;
}

void Camera::Resize(uint16_t width, uint16_t height)
{
	// Update our projection matrix since the window size changed
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	float FoV = 0.25f * 3.1415926535f;
	glm::mat4 P = glm::perspectiveLH(FoV, (float)width / height, 0.1f, 100.0f);

	projectionMatrix = glm::transpose(P);
}