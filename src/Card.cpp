#include "Card.h"
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

	objTexture = new Texture(objRect, path.c_str());
}

Card::~Card()
{
	cardBackTexture = nullptr;
}

void Card::update()
{
	isMoving = UpdateLocation();
}

void Card::render()
{
	if (isFaceSide)
		objTexture->render();
	else
		cardBackTexture->render(objRect);
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


