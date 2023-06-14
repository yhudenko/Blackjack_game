#pragma once

#include <SDL.h>

class BaseObject
{
public:
	BaseObject(SDL_Rect* rect);
	~BaseObject();

	virtual void update() = 0;
	virtual void render() = 0;

protected:
	SDL_Rect* objRect;
};

