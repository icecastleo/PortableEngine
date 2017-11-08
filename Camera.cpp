#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\quaternion.hpp"

using namespace glm;

Camera::Camera()
{

#if defined(DEBUG) | defined(_DEBUG)
	debugMode = true;
#endif // DEBUG

}

Camera::~Camera() 
{
}

void Camera::Init(uint16_t width, uint16_t height)
{
	// FIXME:  
#if _PC
	position = vec3(0.f, 8.f, -15.f);
	rotation = vec3(15.f, 0.f, 0.f);
#endif	
#if _PS4
	position = glm::vec4(5.0f, 5.0f, -20.0f, 0);
	rotation = vec3(15.f, 0.f, 0.f);
#endif

	CreateMatrices(width, height);
}

// Create the base matrices for the camera
void Camera::CreateMatrices(uint16_t width, uint16_t height)
{
	MakeViewMatrix();
	MakeProjectionMatrix(width, height);
}

void Camera::MakeViewMatrix()
{
	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 trans = glm::translate(identity, position);

	mat3 rotationMatrix = toMat3(quat(radians(rotation)));

	static vec3 defaultUp(0.f, 1.f, 0.f);
	static vec3 defaultDir(0.f, 0.f, 1.f);

	direction = rotationMatrix * defaultDir;
	up = rotationMatrix * defaultUp;

	glm::mat4 V = glm::lookAtLH(position, position + direction, up);
	viewMatrix = glm::transpose(V);
}

void Camera::MakeProjectionMatrix(uint16_t width, uint16_t height)
{
	// Update our projection matrix since the window size changed
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	float FoV = 60.f;
	glm::mat4 P = glm::perspectiveFovLH(radians(FoV), (float)width, (float)height, 0.1f, 100.0f);
	projectionMatrix = glm::transpose(P);
}

void Camera::Update(float deltaTime) 
{
	MakeViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

glm::vec3 Camera::GetDirection()
{
	return direction;
}

glm::vec3 Camera::GetPositon()
{
	return position;
}

void Camera::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Camera::SetRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Camera::Resize(uint16_t width, uint16_t height)
{
	MakeProjectionMatrix(width, height);
}