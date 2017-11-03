
#if defined(_PC)  

#include <crtdbg.h>  
#include "WindowsEngine.h"
#include <Windows.h>

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(803);
#endif

	WindowsEngine engine = WindowsEngine(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true);			   // Show extra stats (fps) in title bar?

	engine.Run();


#elif defined(_PS4)  

#include <stdlib.h> 
#include <time.h>
#include "PS4_Engine.h"

int main(int argc, const char *argv[])
{
	srand((unsigned)time(0));

	//
	// Define window size and set up a window to render to it
	//
	uint32_t targetWidth = 1920;
	uint32_t targetHeight = 1080;

	PS4_Engine engine = PS4_Engine(targetWidth,	targetHeight);			  

	engine.Run();
#else  

int main() {

#endif

	return 0;
}
