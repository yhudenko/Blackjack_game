#pragma once
#include <SDL.h>
#include <queue>

class GameObject
{
public:
	GameObject(int xPos, int yPos);
	~GameObject();

	void update();

	void move(int targetX, int targetY);
protected:
	SDL_Rect objRect;
	std::queue<std::pair<int, int>> pathPoints;

	void UpdateLocation();
};

