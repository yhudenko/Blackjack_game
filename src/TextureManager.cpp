#include "TextureManager.h"
#include <SDL_image.h>
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

SDL_Texture* TextureManager::GetTextLabel(const char* text, int size, SDL_Color* color)
{
	TTF_Font* font = TTF_OpenFont("data/arial.ttf", size);
	SDL_Surface* tempSurf = TTF_RenderText_Blended(font, text, *color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tempSurf);
	SDL_FreeSurface(tempSurf);
	TTF_CloseFont(font);
	delete color;
	return texture;
}
