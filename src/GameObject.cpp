#include "GameObject.h"
#include "SDL_Engine.h"

GameObject::GameObject(SDL_Rect* rect) : BaseObject(rect)
{
	
}

GameObject::~GameObject()
{
	delete objTexture;
	objTexture = nullptr;
	while (!pathPoints.empty())
		pathPoints.pop();
}

void GameObject::move(int targetX, int targetY)
{
	int dx = targetX - objRect->x;
	int dy = targetY - objRect->y;

	int animationFrameRate = SDL_Engine::Instance()->animationFrameRate;
	float stepX = static_cast<float>(dx) / animationFrameRate;
	float stepY = static_cast<float>(dy) / animationFrameRate;

	float x = static_cast<float>(objRect->x);
	float y = static_cast<float>(objRect->y);

	for (int i = 0; i < animationFrameRate; i++)
	{
		auto location = std::pair<int, int>(static_cast<int>(x), static_cast<int>(y));
		pathPoints.push(location);

		x += stepX;
		y += stepY;
	}
	auto location = std::pair<int, int>(static_cast<int>(targetX), static_cast<int>(targetY));
	pathPoints.push(location);
}

bool GameObject::UpdateLocation()
{
	if (pathPoints.empty())
		return false;
	objRect->x = pathPoints.front().first;
	objRect->y = pathPoints.front().second;
	pathPoints.pop();
	return true;
}