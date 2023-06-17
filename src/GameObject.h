#pragma once
#include <SDL.h>
#include <queue>

#include "BaseObject.h"

class GameObject : public BaseObject
{
public:
	GameObject(SDL_Rect* rect);
	~GameObject();
	
	void move(int targetX, int targetY);

protected:
	std::queue<std::pair<int, int>> pathPoints;

	bool UpdateLocation();
};

