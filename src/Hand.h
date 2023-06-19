#pragma once

#include <vector>
#include <string>
#include "Card.h"
#include "BaseObject.h"
#include "Deck.h"
#include "Chip.h"

enum class HandStatus
{
	PLAYING,
	WAITRESULT,
	WIN,
	LOSE,
	DRAW
};

class Hand : public BaseObject
{
public:
	Hand(SDL_Rect* dRect, std::string name);
	~Hand();

	HandStatus status = HandStatus::PLAYING;
	bool endTurn = false;
	bool somethingMoving = false;

	void update() override;
	void render() override;

	virtual bool Distribution(Deck* deck) = 0;
	virtual void Turn(Deck* deck, Hand* dealer) = 0;
	virtual HandStatus Results(int dealerValue = 0);

	void Hit(Deck* deck, bool hidden = false);
	void Stand();
	void getChips(int count);
	Texture* getNameLabel();
	void BetChip();
	int getHandSize();
	int calculateValue(bool includeHidden = false);
	void clear();
protected:
	Texture* nameLabel = nullptr;
	Texture* resultLabel = nullptr;
	std::vector<Card*> cards;
	std::deque<Chip*> chips;
	std::deque<Chip*> bet;
	int chipsBaseXPos = 0;
	int chipsBaseYPos = 0;
};


