#include "Chip.h"
#include "Game.h"

Chip::Chip(int xPos, int yPos) : GameObject(new SDL_Rect{ xPos,yPos,192,167 })
{
	objTexture = new Texture("data/Chip.png");
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
	SDL_RenderCopy(Game::GetRenderer(), objTexture->texture, objTexture->sRect, objRect);
}
