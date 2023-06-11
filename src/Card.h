#pragma once

#include <SDL.h>

class Card
{
public:
	Card(int xPos, int yPos, int cardIndex, int suit);
	~Card();

	void update();
	void render();

	int getValue();
private:
	int xPos_;
	int yPos_;
	SDL_Rect cardRect;
	SDL_Texture* cardFaceTexture;
	int value;
};

