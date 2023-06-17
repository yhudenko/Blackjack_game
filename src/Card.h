#pragma once

#include <queue>
#include "GameObject.h"

class Card : public GameObject
{
public:
	Card(SDL_Rect* cardRect, int cardIndex, int suit, Texture* backSideTexture);
	~Card();

	void update() override;
	void render() override;

	int getValue();
	void changeLocation(int xPos, int yPos);

	bool isFaceSide = false;

private:
	Texture* cardBackTexture;
	int value = 0;

};

