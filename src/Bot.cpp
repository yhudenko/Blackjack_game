#include "Bot.h"

Bot::Bot(SDL_Rect* dRect) : Hand(dRect)
{

}

Bot::~Bot()
{

}

bool Bot::Distribution(Deck* deck)
{
	Hit(deck);
	endTurn = true;
	return false;
}

void Bot::Turn(Deck* deck)
{
	if (calculateValue() < 17)
		Hit(deck);
	else
		Stand();
	endTurn = true;
}
