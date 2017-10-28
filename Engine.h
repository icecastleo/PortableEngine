#pragma once

#include <chrono>

#if _PC

#endif

#if _PS4
// PS4 Resource Manager or Material Manager
#endif

#include "RenderSystem.h"
#include "IOSystem.h"

class Engine
{
private:
	//static Engine instance;

public:
	~Engine();

	//static Engine& instance() { return instance; }

	void Run();


#if _PC

#endif

protected:
	Engine();
	virtual bool platformUpdate(float deltaTime) { return true; }

	RenderSystem  *renderSystem;
	IOSystem *ioSystem;

private:
	// Timing related data
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::chrono::time_point<std::chrono::steady_clock> currentTime;
	std::chrono::time_point<std::chrono::steady_clock> previousTime;

	float totalTime;
	float deltaTime;

	//virtual void update(float deltaTime) {}
};

