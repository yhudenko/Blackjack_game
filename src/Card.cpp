#include "Card.h"
#include "TextureManager.h"
#include "Game.h"
#include <string>

const int CARD_HEIGHT = 140;
const int CARD_WIDTH = 100;
const std::string suitNames[]{ "spades", "hearts", "diamonds", "clubs" };

Card::Card(int xPos, int yPos, int cardIndex, int suit) : GameObject(xPos, yPos), isFaceSide(false)
{
	objRect.h = CARD_HEIGHT;
	objRect.w = CARD_WIDTH;

	value = (cardIndex <= 10) ? cardIndex : 10;
	
	std::string path = "data/Card_images/";
	switch (cardIndex)
	{
	case 1:
		path += "ace";
		break;
	case 11:
		path += "jack";
		break;
	case 12:
		path += "queen";
		break;
	case 13:
		path += "king";
		break;
	default:
		path += std::to_string(cardIndex);
		break;
	}
	path += "_of_" + suitNames[suit] + ".png";

	cardFaceTexture = TextureManager::LoadTexture(path.c_str());

	
}

Card::~Card()
{
	SDL_DestroyTexture(cardFaceTexture);
}

void Card::update()
{
	GameObject::update();
}

void Card::render()
{
	if(isFaceSide)
		SDL_RenderCopy(Game::GetRenderer(), cardFaceTexture, NULL, &objRect);
	else
		SDL_RenderCopy(Game::GetRenderer(), cardFaceTexture, NULL, &objRect);
	UpdateLocation();
}

int Card::getValue()
{
	return value;
}


