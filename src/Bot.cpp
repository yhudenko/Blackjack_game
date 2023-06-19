#include "Bot.h"

Bot::Bot(SDL_Rect* dRect, std::string name) : Hand(dRect, name)
{
	getChips(10);
}

Bot::~Bot()
{

}

bool Bot::Distribution(Deck* deck)
{
	Hit(deck);
	return false;
}

void Bot::Turn(Deck* deck, Hand* dealer)
{
	if (bet.empty())
		BetChip();
	if (calculateValue() < 17)
	{
		BetChip();
		Hit(deck);
	}
	else
	{
		if (dealer->calculateValue() <= 7 && dealer->getHandSize() == 2)
		{
			BetChip();
			Hit(deck);
		}
		else
			Stand();
	}
	endTurn = true;
}


