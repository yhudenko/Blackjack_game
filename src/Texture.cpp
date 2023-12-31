#include "Texture.h"
#include "SDL_Engine.h"
#include <iostream>

Texture::Texture(SDL_Rect* rect, const char* imagePath, SDL_Rect* imageSRect) : dRect(rect), sRect(imageSRect)
{
	SDL_Surface* tempSurface = IMG_Load(imagePath);
	texture = SDL_CreateTextureFromSurface(SDL_Engine::Instance()->GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);
}

Texture::Texture(SDL_Rect* rect, const char* labelText, SDL_Color color, float fillPercent) : dRect(rect)
{
	sRect = nullptr;
	
	int maxH = static_cast<int>(static_cast<float>(rect->h) * fillPercent);
	int maxW = static_cast<int>(static_cast<float>(rect->w) * fillPercent);
	
	int minSize = 10;  // Minimum font size
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

		if (textWidth <= maxW && textHeight <= maxH)
			minSize = fontSize + 1;
		else 
			maxSize = fontSize - 1;
	}
	int wSize = 0, hSize = 0;
	TTF_SizeText(font, labelText, &wSize, &hSize);

	offsetRect = new SDL_Rect{ (rect->w - wSize) / 2, (rect->h - hSize) / 2, wSize - rect->w , hSize - rect->h };

	SDL_Surface* tempSurf = TTF_RenderText_Blended(font, labelText, color);
	texture = SDL_CreateTextureFromSurface(SDL_Engine::Instance()->GetRenderer(), tempSurf);
	SDL_FreeSurface(tempSurf);
	TTF_CloseFont(font);
}

Texture::Texture(SDL_Rect* rect, SDL_Color color) : dRect(rect)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	texture = SDL_CreateTextureFromSurface(SDL_Engine::Instance()->GetRenderer(), surface);
}

Texture::~Texture()
{
	delete sRect;
	delete offsetRect;
	offsetRect = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Texture::render()
{
	if (offsetRect)
	{
		SDL_Rect destRect = { dRect->x + offsetRect->x,  dRect->y + offsetRect->y, dRect->w + offsetRect->w, dRect->h + offsetRect->h };
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, &destRect);
	}
	else
	{
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, dRect);
	}
}

void Texture::render(int xPos, int yPos)
{
	if (offsetRect)
	{
		SDL_Rect destRect = { xPos + offsetRect->x,  yPos + offsetRect->y, dRect->w + offsetRect->w, dRect->h + offsetRect->h };
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, &destRect);
	}
	else
	{
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, dRect);
	}
}

void Texture::render(SDL_Rect* rect)
{
	if (offsetRect)
	{
		SDL_Rect destRect = { rect->x + offsetRect->x,  rect->y + offsetRect->y, rect->w + offsetRect->w, rect->h + offsetRect->h };
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, &destRect);
	}
	else
	{
		SDL_RenderCopy(SDL_Engine::Instance()->GetRenderer(), texture, sRect, rect);
	}
}

void Texture::changeSRect(SDL_Rect& rect)
{
	sRect->x = rect.x;
	sRect->y = rect.y;
	sRect->w = rect.w;
	sRect->h = rect.h;
}

