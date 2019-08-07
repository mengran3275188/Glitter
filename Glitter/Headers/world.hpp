#pragma once

// Standard Headers
#include <vector>

// Local Headers
#include "gameobject.hpp"
#include "camera.hpp"

class World
{
public:
	void Init();
	void Render(Camera camera);

private:
	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mLights;
};
