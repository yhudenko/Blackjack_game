#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer)
	{
		SDL_Surface* tempSurface = IMG_Load(fileName);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		
		return texture;
	}

};
