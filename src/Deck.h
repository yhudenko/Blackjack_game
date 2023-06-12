#pragma once
#include "Card.h"
#include  <deque>

class Deck
{
public:
	Deck(const int xPos = 0, const int yPos = 0);
	~Deck();

	void update();
	void render();

	Card* GetCard();

	static SDL_Texture* cardBackSideTexture;

private:
	std::deque<Card*> cardDeck;
};

