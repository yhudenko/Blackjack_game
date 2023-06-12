#include "Button.h"
#include "Game.h"

Button::Button(std::string buttonName, SDL_Rect* destinationRect, SDL_Texture* buttonTexture, SDL_Rect* sourceRect)
{
	name = buttonName;
	dRect = destinationRect;
	texture = buttonTexture;
	sRect = sourceRect;
}

Button::~Button()
{
	SDL_DestroyTexture(texture);
	delete sRect;
	delete dRect;
}

void Button::update()
{
	if (isHidden)
		return;
	isSelected = SDL_HasIntersection(dRect, Game::mousePos);
}

void Button::render()
{
	if (isHidden)
		return;
	if(texture)
		SDL_RenderCopy(Game::GetRenderer(), texture, sRect, dRect);
	else
	{
		SDL_RenderDrawRect(Game::GetRenderer(), dRect);
	}
}

