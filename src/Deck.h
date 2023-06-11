#pragma once
#include "Card.h"
#include  <deque>

class Deck
{
public:
	Deck(int xPos, int yPos);
	~Deck();

	void update();
	void render();

private:
	int xPos_;
	int yPos_;
	std::deque<Card*> cardDeck;
};

