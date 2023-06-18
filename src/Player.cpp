#include "Player.h"

Player::Player(SDL_Rect* dRect) : Hand(dRect)
{
	getChips();
}

Player::~Player()
{

}

bool Player::Distribution(Deck* deck)
{
	Hit(deck);
	endTurn = true;
	return false;
}

void Player::Turn(Deck* deck)
{
	
}



