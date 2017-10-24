
#include "Game.h"
#include "PC_Engine.h"

#if _PC
#include <Windows.h>
//typedef float gFloat;
#endif

#if _PS4
// PS4 Resource Manager or Material Manager
#endif

// --------------------------------------------------------
// Entry point for a graphical (non-console) Windows application
// --------------------------------------------------------
int WINAPI WinMain(
	HINSTANCE hInstance,		// The handle to this app's instance
	HINSTANCE hPrevInstance,	// A handle to the previous instance of the app (always NULL)
	LPSTR lpCmdLine,			// Command line params
	int nCmdShow)				// How the window should be shown (we ignore this)
{
#if defined(DEBUG) | defined(_DEBUG)
	// Enable memory leak detection as a quick and dirty
	// way of determining if we forgot to clean something up
	//  - You may want to use something more advanced, like Visual Leak Detector
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(1477);
#endif

#if _PC
	PC_Engine engine = PC_Engine(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true);			   // Show extra stats (fps) in title bar?

	engine.Run();
#endif

#if _PS4
	// PS4 Resource Manager or Material Manager
#endif

	//// Create the Game object using
	//// the app handle we got from WinMain
	//Game dxGame(hInstance);

	//// Result variable for function calls below
	//HRESULT hr = S_OK;

	//// Attempt to create the window for our program, and
	//// exit early if something failed
	//hr = dxGame.InitWindow();
	//if(FAILED(hr)) return hr;

	//// Attempt to initialize DirectX, and exit
	//// early if something failed
	//hr = dxGame.InitDirectX();
	//if(FAILED(hr)) return hr;

	//// Begin the message and game loop, and then return
	//// whatever we get back once the game loop is over
	//return dxGame.Run();

	return 0;
}
