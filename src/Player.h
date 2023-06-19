#pragma once
#include "Hand.h"
class Player : public Hand
{
public:
	Player(SDL_Rect* dRect, std::string name);
	~Player();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck, Hand* dealer) override;
	
protected:

};

