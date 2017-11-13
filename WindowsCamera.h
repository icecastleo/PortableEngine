#pragma once
#include "Camera.h"
#include <Windows.h>

class WindowsCamera :
	public Camera
{
public:
	WindowsCamera(uint16_t width, uint16_t height);
	~WindowsCamera();

	void Update(float) override;
};

