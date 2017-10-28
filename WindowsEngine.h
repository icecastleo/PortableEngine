#pragma once
#include "Engine.h"
#include <string>
#include <Windows.h>

class WindowsEngine :
	public Engine
{
public:
	WindowsEngine(
		HINSTANCE hInstance,		// The application's handle
		char* titleBarText,			// Text for the window's title bar
		unsigned int windowWidth,	// Width of the window's client area
		unsigned int windowHeight,	// Height of the window's client area
		bool debugTitleBarStats);	// Show extra stats (fps) in title bar?);

	~WindowsEngine();

	HRESULT InitWindow(HINSTANCE hInstance);

	static WindowsEngine* EngineInstance;
	static LRESULT CALLBACK WindowProc(
		HWND hWnd,		// Window handle
		UINT uMsg,		// Message
		WPARAM wParam,	// Message's first parameter
		LPARAM lParam	// Message's second parameter
	);

	// Internal method for message handling
	LRESULT ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	 bool platformUpdate(float) override;

private:
	HINSTANCE	hInstance;		// The handle to the application
	HWND		hWnd;			// The handle to the window itself
	std::string titleBarText;	// Custom text in window's title bar
	bool		titleBarStats;	// Show extra stats in title bar?

								// Size of the window's client area
	unsigned int width;
	unsigned int height;

	int fpsFrameCount;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	// Helper function for allocating a console window
	void CreateConsoleWindow(int bufferLines, int bufferColumns, int windowLines, int windowColumns);
	void UpdateTitleBarStats(float deltaTime);	// Puts debug info in the title bar

	//Camera Cam;

	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta, int x, int y);
};

