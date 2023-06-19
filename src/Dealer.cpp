#include "Dealer.h"
#include <iostream>
Dealer::Dealer(SDL_Rect* dRect, std::string name) : Hand(dRect, name)
{

}

Dealer::~Dealer()
{

}

bool Dealer::Distribution(Deck* deck)
{
	switch (cards.size())
	{
	case 0:
		Hit(deck, true);
		break;
	case 1:
		Hit(deck);
		endTurn = true;
		return true;
		break;
	default:
		break;
	}
	return false;
}

void Dealer::Turn(Deck* deck, Hand* dealer)
{
	if (calculateValue(true) < 17)
		Hit(deck);
	else
		Stand();
	endTurn = true;
}

HandStatus Dealer::Results(int dealerValue)
{
	cards.front()->isFaceSide = true;
	if (calculateValue() > 21)
		status = HandStatus::LOSE;
	return status;
}


