#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(SDL_Rect* rect) : BaseObject(rect)
{
	
}

GameObject::~GameObject()
{
	while (!pathPoints.empty())
		pathPoints.pop();
}

void GameObject::move(int targetX, int targetY)
{
	int dx = targetX - objRect->x;
	int dy = targetY - objRect->y;

	float stepX = static_cast<float>(dx) / Game::animationFrameRate;
	float stepY = static_cast<float>(dy) / Game::animationFrameRate;

	float x = static_cast<float>(objRect->x);
	float y = static_cast<float>(objRect->y);

	for (int i = 0; i <= Game::animationFrameRate; i++)
	{
		auto location = std::pair<int, int>(static_cast<int>(x), static_cast<int>(y));

		pathPoints.push(location);

		x += stepX;
		y += stepY;
	}
}

void GameObject::UpdateLocation()
{
	if (pathPoints.empty())
		return;
	pathPoints.front().first;
	objRect->x = pathPoints.front().first;
	objRect->y = pathPoints.front().second;
	pathPoints.pop();
}