#pragma once
#include "Card.h"
#include  <deque>

class Deck : public BaseObject
{
public:
	Deck(const int xPos, const int yPos);
	~Deck();

	void update() override;
	void render() override;

	Card* GetCard(bool hidden = false);
	void ChangeCardBackSide();

private:
	std::deque<Card*> cardDeck;
	int cardBackSideIndex = 0;
	Texture* cardBackSideTexture;

	void shuffleDeck();
};

