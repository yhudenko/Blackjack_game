#include "Texture.h"
#include "Game.h"

#include <SDL_ttf.h>

Texture::Texture(const char* imagePath, SDL_Rect* imageSRect) : sRect(imageSRect)
{
	SDL_Surface* tempSurface = IMG_Load(imagePath);
	texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);
}

Texture::Texture(const char* labelText, int fontSize, SDL_Color color)
{
	sRect = nullptr;
	TTF_Font* font = TTF_OpenFont("data/arial.ttf", fontSize);
	SDL_Surface* tempSurf = TTF_RenderText_Blended(font, labelText, color);
	texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tempSurf);
	SDL_FreeSurface(tempSurf);
	TTF_CloseFont(font);
}

Texture::Texture(int width, int height, SDL_Color color)
{
	sRect = nullptr;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);
}

Texture::~Texture()
{
	delete sRect;
	SDL_DestroyTexture(texture);
}

