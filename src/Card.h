#pragma once

#include <SDL.h>
#include <queue>
#include "GameObject.h"

class Card : public GameObject
{
public:
	Card(int xPos = 0, int yPos = 0, int cardIndex = 1, int suit = 0);
	~Card();

	void update();
	void render();

	int getValue();

private:
	SDL_Texture* cardFaceTexture;
	bool isFaceSide;
	int value;

};

