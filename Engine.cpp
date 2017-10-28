#include "Engine.h"

using ms = std::chrono::duration<float, std::milli>;

Engine::Engine()
{
//#if _PC
//	renderSystem = new Game();
//#endif
//
//#if _PS4
//	// PS4 Resource Manager or Material Manager
//#endif
}

Engine::~Engine()
{
	if (renderSystem)
		delete renderSystem;
}

//IOSystem *IOSystem::IO_instance = 0;

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
		stop = platformUpdate(deltaTime);

		// Save current time for next frame
		previousTime = currentTime;
	}
}