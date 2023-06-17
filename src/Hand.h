#pragma once
#include "Card.h"
#include "BaseObject.h"
#include "Deck.h"
#include <vector>

enum class HandStatus
{
	PLAYING,
	WAITRESULT,
	WIN,
	LOSE
};

class Hand : public BaseObject
{
public:
	Hand(SDL_Rect* dRect);
	~Hand();

	HandStatus status = HandStatus::PLAYING;
	bool currentTurn = false;
	bool endTurn = false;
	bool cardMoving = false;

	void update() override;
	void render() override;

	virtual bool Distribution(Deck* deck) = 0;
	virtual void Turn(Deck* deck) = 0;

	void Hit(Deck* deck);
	void Stand();
protected:
	std::vector<Card*> cards;

	int calculateValue();
};


