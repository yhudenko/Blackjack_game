#pragma once
#include "Card.h"
#include <vector>

enum HandType
{
	BOT = 0,
	DEALER,
	PLAYER
};

class Hand
{
public:
	Hand(const int xPos = 0, const int yPos = 0, HandType type = BOT);
	~Hand();

	void update();
	void render();

	bool currentTurn = false;
	bool endTurn = false;

private:
	HandType handType;
	SDL_Rect handRect;
	std::vector<Card*> cards;
};

