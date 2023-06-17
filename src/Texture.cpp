#include "Texture.h"
#include "Game.h"
#include <iostream>
#include <SDL_ttf.h>

Texture::Texture(const char* imagePath, SDL_Rect* imageSRect) : sRect(imageSRect)
{
	SDL_Surface* tempSurface = IMG_Load(imagePath);
	texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);
}

Texture::Texture(const char* labelText, SDL_Rect* size, SDL_Color color)
{
	sRect = nullptr;
	
	int minSize = 20;  // Minimum font size
	int maxSize = 200; // Maximum font size
	TTF_Font* font = nullptr;

	// Perform binary search font size
	while (minSize <= maxSize) 
	{
		if (font)
		{
			TTF_CloseFont(font);
			font = nullptr;
		}

		int fontSize = (minSize + maxSize) / 2;

		font = TTF_OpenFont("data/arial.ttf", fontSize);
		if (!font) {
			std::cout << "Label Load Font FAIL" << std::endl;
			break;
		}

		int textWidth, textHeight;
		if (TTF_SizeText(font, labelText, &textWidth, &textHeight) == -1) {
			TTF_CloseFont(font);
			std::cout << "Label Size FAIL" << std::endl;
			break;
		}

		if (textWidth <= size->w && textHeight <= size->h)
			minSize = fontSize + 1;
		else 
			maxSize = fontSize - 1;
	}
	TTF_SizeText(font, labelText, &(size->w), &(size->h));

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
