#pragma once
#include "Hand.h"
class Bot : public Hand
{
public:
	Bot(SDL_Rect* dRect);
	~Bot();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck) override;

protected:

};

