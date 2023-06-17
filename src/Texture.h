#pragma once

#include <SDL.h>

class Texture
{
public:
	Texture(const char* imagePath, SDL_Rect* imageSRect = nullptr);
	Texture(const char* labelText, SDL_Rect* size, SDL_Color color);
	Texture(int width, int height, SDL_Color color);
	~Texture();

	SDL_Rect* sRect;
	SDL_Texture* texture;	
};

