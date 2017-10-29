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
	virtual bool platformUpdate() { return true; }

	float deltaTime;
	float totalTime;

	RenderSystem  *renderSystem;
	//IOSystem *ioSystem;

private:
	// Timing related data
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point previousTime;

	//virtual void update(float deltaTime) {}
};

