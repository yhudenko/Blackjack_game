#pragma once
#include "Hand.h"
class Player : public Hand
{
public:
	Player(SDL_Rect* dRect);
	~Player();

	bool Distribution(Deck* deck) override;
	void Turn(Deck* deck) override;
	
protected:

};

