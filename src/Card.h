#pragma once

#include "TextureManager.h"
#include <string>



class Card
{
public:
	Card(int xPos, int yPos, int cardIndex, int suit, SDL_Renderer* renderer);
	~Card();

	void update();
	void render();

	int getValue();
private:
	int xPos_;
	int yPos_;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer_;
	SDL_Texture* cardFaceTexture;
	int value;
};

