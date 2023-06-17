#include "Card.h"
#include "Game.h"
#include <string>


const std::string suitNames[]{ "spades", "hearts", "diamonds", "clubs" };

Card::Card(SDL_Rect* cardRect, int cardIndex, int suit, Texture* backSideTexture) : GameObject(cardRect), cardBackTexture(backSideTexture)
{
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

	cardFaceTexture = new Texture(path.c_str());
}

Card::~Card()
{
	cardBackTexture = nullptr;
	delete cardFaceTexture;

}

void Card::update()
{
	isMoving = UpdateLocation();
}

void Card::render()
{
	if(isFaceSide)
		SDL_RenderCopy(Game::GetRenderer(), cardFaceTexture->texture, cardFaceTexture->sRect, objRect);
	else
		SDL_RenderCopy(Game::GetRenderer(), cardBackTexture->texture, cardBackTexture->sRect, objRect);
}

int Card::getValue()
{
	return value;
}

void Card::changeLocation(int xPos, int yPos)
{
	objRect->x = xPos;
	objRect->y = yPos;
}


