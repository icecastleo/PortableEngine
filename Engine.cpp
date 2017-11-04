#include "Engine.h"

using ms = std::chrono::duration<float, std::milli>;

IOSystem *Engine::ioSystem = 0;

Engine::Engine()
{

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
		stop = platformUpdate();

		// Save current time for next frame
		previousTime = currentTime;
	}
}