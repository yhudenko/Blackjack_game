#include "Dealer.h"

Dealer::Dealer(SDL_Rect* dRect) : Hand(dRect)
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
		cards.push_back(deck->GetCard(true));
		cards.back()->move(objRect->x + 30 * static_cast<int>(cards.size()), objRect->y + 30 * static_cast<int>(cards.size()));
		break;
	case 1:
		Hit(deck);
		endTurn = true;
		return true;
		break;
	default:
		break;
	}
	endTurn = true;
	return false;
}

void Dealer::Turn(Deck* deck)
{
	if (calculateValue() < 17)
	{
		cards.push_back(deck->GetCard());
		cards.back()->move(objRect->x + 30 * static_cast<int>(cards.size()), objRect->y + 30 * static_cast<int>(cards.size()));
	}
	else
		Stand();
	endTurn = true;
}

