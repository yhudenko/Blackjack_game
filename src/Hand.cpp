#include "Hand.h"

Hand::Hand(SDL_Rect* dRect) : BaseObject(dRect)
{
	for (int i = 0; i < 10; ++i)
	{
		//chips.push_back(new Chip(dRect));
	}
}

Hand::~Hand()
{
	for (auto card : cards)
		delete card;
	cards.clear();
}

void Hand::update()
{
	for (auto card : cards)
		card->update();

	if (currentTurn)
		cardMoving = cards.back()->isMoving;
}

void Hand::render()
{
	for (auto card : cards)
		card->render();
}

void Hand::Hit(Deck* deck)
{
	cards.push_back(deck->GetCard());
	cards.back()->move(objRect->x + 30 * cards.size(), objRect->y + 30 * cards.size());
	int currentValue = calculateValue();
	if (currentValue == 21)
		status = HandStatus::WIN;
	if (currentValue > 21)
		status = HandStatus::LOSE;
	endTurn = true;
}

void Hand::Stand()
{
	status == HandStatus::WAITRESULT;
}

int Hand::calculateValue()
{
	int totalValue = 0;
	bool ace = false;
	for (auto card : cards)
	{
		if (card->getValue() == 1)
			ace = true;
		totalValue += card->getValue();
	}
	if (ace)
		totalValue = ((totalValue + 10) <= 21) ? totalValue + 10 : totalValue;

	return totalValue;
}