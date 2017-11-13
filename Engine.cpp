#include "Engine.h"
#include <gainput/gainput.h>

#if defined(_PC)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
//#include <windows.h>
//
//#include <stdio.h>
#define LOG(...) {char buf[256]; sprintf(buf, __VA_ARGS__); OutputDebugStringA(buf); }

#endif

using ms = std::chrono::duration<float, std::milli>;

IOSystem *Engine::ioSystem = 0;

// Define your user buttons
enum Button
{
	ButtonMenu,
	ButtonConfirm,
	MouseX,
	MouseY
};

Engine::Engine(uint16_t windowsWidth, uint16_t windowsHeight)
	:width(windowsWidth), height(windowsHeight)
{
	// Setup Gainput
	gainput::InputManager manager;
	manager.SetDisplaySize(width, height);
	gainput::DeviceId mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();
	gainput::DeviceId keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
	gainput::DeviceId padId = manager.CreateDevice<gainput::InputDevicePad>();

	gainput::InputMap map(manager);
	map.MapBool(ButtonMenu, keyboardId, gainput::KeyEscape);
	map.MapBool(ButtonConfirm, mouseId, gainput::MouseButtonLeft);
	map.MapFloat(MouseX, mouseId, gainput::MouseAxisX);
	map.MapFloat(MouseY, mouseId, gainput::MouseAxisY);
	map.MapBool(ButtonConfirm, padId, gainput::PadButtonA);

	while (!doExit)
	{
		// Update Gainput
		manager.Update();

		MSG msg;
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// Forward any input messages to Gainput
			manager.HandleMessage(msg);
		}

		// Check button states
		if (map.GetBoolWasDown(ButtonConfirm))
		{
			gainput::InputDevicePad* pad = static_cast<gainput::InputDevicePad*>(manager.GetDevice(padId));
			pad->Vibrate(1.0f, 0.0f);
		}
		if (map.GetBoolWasDown(ButtonMenu))
		{
			gainput::InputDevicePad* pad = static_cast<gainput::InputDevicePad*>(manager.GetDevice(padId));
			pad->Vibrate(0.0f, 0.0f);
		}

		if (map.GetBoolWasDown(ButtonMenu))
		{
			LOG("Open Menu!!\n");
		}
		if (map.GetBoolWasDown(ButtonConfirm))
		{
			LOG("Confirmed!!\n");
		}

		if (map.GetFloatDelta(MouseX) != 0.0f || map.GetFloatDelta(MouseY) != 0.0f)
		{
			LOG("Mouse: %f, %f\n", map.GetFloat(MouseX), map.GetFloat(MouseY));
		}
	}

	

}

Engine::~Engine()
{
	
}

void Engine::Run()
{
	bool stop = false;

	startTime = std::chrono::steady_clock::now();
	previousTime = startTime;

	while (!stop) {
		
		currentTime = std::chrono::steady_clock::now();

		deltaTime = std::chrono::duration_cast<ms>(currentTime - previousTime).count() / 1000.f;
		totalTime = std::chrono::duration_cast<ms>(currentTime - startTime).count() / 1000.f;

		renderSystem->Update(deltaTime);
		renderSystem->Draw();

		// check if stop the game
		stop = Update();

		// Save current time for next frame
		previousTime = currentTime;
	}
}