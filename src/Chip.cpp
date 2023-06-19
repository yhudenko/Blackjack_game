#include "Chip.h"

Chip::Chip(int xPos, int yPos) : GameObject(new SDL_Rect{ xPos, yPos, CHIP_WIDTH, CHIP_HEIGHT})
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
