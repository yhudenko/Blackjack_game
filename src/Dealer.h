#pragma once
#include "Hand.h"
class Dealer : public Hand
{
public:
	Dealer(SDL_Rect* dRect, std::string name);
	~Dealer();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck, Hand* dealer) override;
	HandStatus Results(int dealerValue = 0) override;
protected:

};

