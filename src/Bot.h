#pragma once
#include "Hand.h"
class Bot : public Hand
{
public:
	Bot(SDL_Rect* dRect, std::string name);
	~Bot();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck, Hand* dealer) override;

protected:

};

