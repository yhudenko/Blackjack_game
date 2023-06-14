#pragma once
#include "Card.h"
#include <vector>

class Hand
{
public:
	Hand(const int xPos, const int yPos);
	~Hand();

	void update();
	void render();

	bool currentTurn = false;
	bool endTurn = false;

private:
	SDL_Rect handRect;
	std::vector<Card*> cards;
};

