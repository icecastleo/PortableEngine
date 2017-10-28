#pragma once

#include <vector>
#include "Entity.h"

class DemoScene
{
public:
	DemoScene();
	~DemoScene();

	std::vector<Entity> entities;
};

