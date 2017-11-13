#include "Engine.h"

using ms = std::chrono::duration<float, std::milli>;

IOSystem *Engine::ioSystem = 0;

// TODO: Move width height to render 
Engine::Engine(uint16_t windowsWidth, uint16_t windowsHeight)
	:width(windowsWidth), height(windowsHeight)
{
	

}

Engine::~Engine()
{
	
}
void Engine::initScene()
{
	SceneBuild.Init();
	SceneManag.AddScene(SceneBuild.GetScene(1));
	SceneManag.AddScene(SceneBuild.GetScene(2));
	SceneManag.AddScene(SceneBuild.GetScene(3));
	SceneManag.AddScene(SceneBuild.GetScene(4));
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