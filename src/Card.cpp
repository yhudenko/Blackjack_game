#include "Card.h"

Card::Card(int xPos, int yPos, int cardIndex, int suit, SDL_Renderer* renderer) : xPos_(xPos), yPos_(yPos), renderer_(renderer)
{
	const std::string suitNames[]{ "spades", "hearts", "diamonds", "clubs" };
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

	cardFaceTexture = TextureManager::LoadTexture(path.c_str(), renderer);

	srcRect.x = xPos;
	srcRect.y = yPos;
	srcRect.h = 175;
	srcRect.w = 125;
}

Card::~Card()
{
	SDL_DestroyTexture(cardFaceTexture);
}

void Card::update()
{

}

void Card::render()
{
	SDL_RenderCopy(renderer_, cardFaceTexture, NULL, &srcRect);
}

int Card::getValue()
{
	return value;
}
