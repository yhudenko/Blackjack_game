#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* GetTextLabel(const char* text, int size, SDL_Color* color);

};
