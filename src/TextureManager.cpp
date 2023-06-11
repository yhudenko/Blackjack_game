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
