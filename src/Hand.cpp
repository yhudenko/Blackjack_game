#include "Hand.h"

Hand::Hand(SDL_Rect* dRect, std::string name) : BaseObject(dRect)
{
	SDL_Rect* tempRect = new SDL_Rect{ dRect->x, dRect->y - 50, dRect->w, 50 };
	nameLabel = new Texture(tempRect, name.c_str(), SDL_Color{ 0, 0, 0 });
	chipsBaseXPos = objRect->x + objRect->w / 2 - CHIP_WIDTH / 2;
	chipsBaseYPos = objRect->y + 300;
}

Hand::~Hand()
{
	for (auto card : cards)
		delete card;
	cards.clear();
	for (auto chip : chips)
		delete chip;
	chips.clear();
	delete nameLabel;
}

void Hand::update()
{
	for (auto card : cards)
		card->update();
	for (auto chip : chips)
		chip->update();
	for (auto chip : bet)
		chip->update();

	bool cardMoving = (cards.size() > 0) ? cards.back()->isMoving : false;
	bool chipsMoving = (chips.size() > 0) ? chips.back()->isMoving : false;
	bool betMoving = (bet.size() > 0) ? bet.back()->isMoving : false;
	somethingMoving = cardMoving || chipsMoving || betMoving;
		
}

void Hand::render()
{
	//Avoid overlapping cards
	for (auto chip : chips)
		chip->render();

	for (auto card : cards)
		card->render();
	
	if(nameLabel) nameLabel->render();
	if(resultLabel) resultLabel->render();

	for (auto chip : bet)
		chip->render();
	
}

HandStatus Hand::Results(int dealerValue)
{
	int value = calculateValue();
	if (dealerValue > 21)
		status = HandStatus::WIN;
	else if (value < dealerValue)
		status = HandStatus::LOSE;
	else if (value == dealerValue)
		status = HandStatus::DRAW;
	else if (value > dealerValue && value <= 21)
		status = HandStatus::WIN;
	else
		status = HandStatus::LOSE;

	std::string labelText;
	SDL_Color labelColor;
	switch (status)
	{
	case HandStatus::WIN:
	{
		labelText = "Win";
		labelColor = SDL_Color{ 0, 255, 0 };
		getChips(static_cast<int>(bet.size()));
		while(!bet.empty())
		{
			Chip* tempChip = bet.back();
			bet.pop_back();
			
			int count = static_cast<int>(chips.size());
			tempChip->move(chipsBaseXPos, chipsBaseYPos - count * 9);
			chips.push_back(tempChip);
		}
	}
		break;
	case HandStatus::LOSE:
		labelText = "Lose";
		labelColor = SDL_Color{ 255, 0, 0 };
		for (auto chip : bet)
			delete chip;
		bet.clear();
		break;
	case HandStatus::DRAW:
		labelText = "Draw";
		labelColor = SDL_Color{ 0, 0, 0 };
		while (!bet.empty())
		{
			Chip* tempChip = bet.back();
			bet.pop_back();

			int count = static_cast<int>(chips.size());
			tempChip->move(chipsBaseXPos, chipsBaseYPos - count * 9);
			chips.push_back(tempChip);
		}
		break;
	default:
		break;
	}
	SDL_Rect* tempRect = new SDL_Rect{ objRect->x, objRect->y - 70, objRect->w, 20 };
	resultLabel = new Texture(tempRect, labelText.c_str(), labelColor);
	return status;
}

bool Hand::CanContinue()
{
	return true;
}

void Hand::Hit(Deck* deck, bool hidden)
{
	int xPos = objRect->x + 30 * static_cast<int>(cards.size());
	int yPos = objRect->y + 30 * static_cast<int>(cards.size());
	cards.push_back(deck->GetCard(hidden));
	cards.back()->move(xPos, yPos);
	endTurn = true;
}

void Hand::Stand()
{
	status = HandStatus::WAITRESULT;
	endTurn = true;
}

void Hand::getChips(int count)
{
	for (int i = 0; i < count; ++i)
	{
		int count = static_cast<int>(chips.size());
		chips.push_back(new Chip(chipsBaseXPos, chipsBaseYPos - count * 9));
	}
}

Texture* Hand::getNameLabel()
{
	return nameLabel;
}

void Hand::BetChip()
{
	if (chips.empty())
	{
		status = HandStatus::LOSE;
		return;
	}
	Chip* chip = chips.back();
	chips.pop_back();
	
	int yPos = objRect->y - static_cast<int>(bet.size()) * 9 - 120;
	chip->move(chipsBaseXPos, yPos);
	bet.push_back(chip);
}

int Hand::getHandSize()
{
	return static_cast<int>(cards.size());
}

int Hand::calculateValue(bool includeHidden)
{
	int totalValue = 0;
	bool ace = false;
	for (auto card : cards)
	{
		if (card->isFaceSide || includeHidden)
		{
			if (card->getValue() == 1)
				ace = true;
			totalValue += card->getValue();
		}
	}
	if (ace)
		totalValue = ((totalValue + 10) <= 21) ? totalValue + 10 : totalValue;

	return totalValue;
}

void Hand::clear()
{
	status = HandStatus::PLAYING;
	for (auto card : cards)
		delete card;
	cards.clear();
	delete resultLabel;
	resultLabel = nullptr;
}
