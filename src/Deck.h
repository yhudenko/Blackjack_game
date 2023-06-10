#pragma once
#include "Card.h"
#include  <deque>

class Deck
{
public:
	Deck();
	~Deck();

	void init(int xPos, int yPos, SDL_Renderer* renderer);
	void update();
	void render();

private:
	int xPos_;
	int yPos_;
	std::deque<Card*> cardDeck;
};

