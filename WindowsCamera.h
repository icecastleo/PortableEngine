#pragma once
#include "Camera.h"
#include <Windows.h>

class WindowsCamera :
	public Camera
{
public:
	WindowsCamera();
	~WindowsCamera();

	void Update(float) override;
};

