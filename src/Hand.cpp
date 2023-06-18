#include "Hand.h"

Hand::Hand(SDL_Rect* dRect) : BaseObject(dRect)
{
	
}

Hand::~Hand()
{
	for (auto card : cards)
		delete card;
	cards.clear();
	for (auto chip : chips)
		delete chip;
	chips.clear();
}

void Hand::update()
{
	for (auto card : cards)
		card->update();
	for (auto chip : chips)
		chip->update();

	if (currentTurn)
		cardMoving = cards.back()->isMoving;
}

void Hand::render()
{
	//Avoid overlapping cards
	for (auto chip : chips)
		chip->render();

	for (auto card : cards)
		card->render();
}

void Hand::Hit(Deck* deck, bool hidden)
{
	int xPos = objRect->x + 30 * static_cast<int>(cards.size());
	int yPos = objRect->y + 30 * static_cast<int>(cards.size());
	cards.push_back(deck->GetCard(hidden));
	cards.back()->move(xPos, yPos);
	int currentValue = calculateValue();
	if (currentValue == 21)
		status = HandStatus::WIN;
	if (currentValue > 21)
		status = HandStatus::LOSE;
	endTurn = true;
}

void Hand::Stand()
{
	status = HandStatus::WAITRESULT;
}

void Hand::getChips()
{
	for (int i = 0; i < 10; ++i)
	{
		int xPos = objRect->x + objRect->w / 2;
		int yPos = objRect->y - i * 9;
		chips.push_back(new Chip(xPos, yPos));
	}
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