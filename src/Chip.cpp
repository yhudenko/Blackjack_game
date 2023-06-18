#include "Chip.h"

const int CHIP_WIDTH = 80;
const int CHIP_HEIGHT = 70;

Chip::Chip(int xPos, int yPos) : GameObject(new SDL_Rect{ xPos - CHIP_WIDTH / 2, yPos + 300, CHIP_WIDTH, CHIP_HEIGHT})
{
	objTexture = new Texture(objRect, "data/Chip.png");
}

Chip::~Chip()
{

}

void Chip::update()
{
	isMoving = UpdateLocation();
}

void Chip::render()
{
	objTexture->render();
}
