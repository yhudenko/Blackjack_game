#pragma once

#include <SDL.h>

class Texture
{
public:
	Texture(SDL_Rect* rect, const char* imagePath, SDL_Rect* imageSRect = nullptr);
	Texture(SDL_Rect* rect, const char* labelText, SDL_Color color, float fillPercent = 0.9f);
	Texture(SDL_Rect* rect, SDL_Color color);
	~Texture();

	void render();
	void render(SDL_Rect* rect);
	void changeSRect(SDL_Rect& rect);

protected:
	SDL_Rect* sRect = nullptr;
	SDL_Rect* dRect = nullptr;
	SDL_Rect* offsetRect = nullptr;
	SDL_Texture* texture = nullptr;
};

