#pragma once

#include <chrono>
#include "RenderSystem.h"
#include "IOSystem.h"
#include "SceneManager.h"
#include "SceneBuilder.h"

class Engine
{
private:
	//static Engine instance;

public:
	~Engine();

	//static Engine& instance() { return instance; }

	void Run();

	// FIXME:
	static IOSystem *ioSystem;

	void initScene();

protected:
	Engine(uint16_t windowsWidth, uint16_t windowsHeight);

	// Size of the window's client area
	uint16_t width;
	uint16_t height;
	
	float deltaTime;
	float totalTime;

	// init by child
	RenderSystem *renderSystem;

	// return ture to stop the game loop
	virtual bool Update() { return true; }

    SceneBuilder SceneBuild;
	SceneManager SceneManag;
private:
	// Timing related data
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point previousTime;
};

