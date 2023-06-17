#pragma once
#include <SDL.h>
#include <queue>

#include "BaseObject.h"
#include "Texture.h"

class GameObject : public BaseObject
{
public:
	GameObject(SDL_Rect* rect);
	~GameObject();
	
	void move(int targetX, int targetY);

	bool isMoving = false;

protected:
	Texture* objTexture = nullptr;
	std::queue<std::pair<int, int>> pathPoints;

	bool UpdateLocation();
};

