#pragma once
#include "Hand.h"
class Dealer : public Hand
{
public:
	Dealer(SDL_Rect* dRect);
	~Dealer();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck) override;

protected:

};

