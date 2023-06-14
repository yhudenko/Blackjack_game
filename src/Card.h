#pragma once

#include <SDL.h>
#include <queue>
#include "GameObject.h"
#include "Texture.h"

class Card : public GameObject
{
public:
	Card(SDL_Rect* cardRect, int cardIndex, int suit, Texture* backSideTexture);
	~Card();

	void update() override;
	void render() override;

	int getValue();

private:
	Texture* cardFaceTexture;
	Texture* cardBackTexture;
	bool isFaceSide;
	int value;

};

