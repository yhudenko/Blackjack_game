#include "Player.h"

Player::Player(SDL_Rect* dRect, std::string name) : Hand(dRect, name)
{
	getChips(10);
}

Player::~Player()
{

}

bool Player::Distribution(Deck* deck)
{
	Hit(deck);
	return false;
}

void Player::Turn(Deck* deck, Hand* dealer)
{
	if (bet.empty() && !chips.empty())
		BetChip();
}

bool Player::CanContinue()
{
	if (chips.empty())
		return false;
	else
		return true;
}




