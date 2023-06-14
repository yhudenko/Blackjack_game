#pragma once
#include "Card.h"
#include  <deque>

class Deck
{
public:
	Deck(const int xPos, const int yPos);
	~Deck();

	void update();
	void render();

	Card* GetCard();
	void ChangeCardBackSide();

private:
	std::deque<Card*> cardDeck;
	int cardBackSideIndex = 0;
	Texture* cardBackSideTexture;
};

