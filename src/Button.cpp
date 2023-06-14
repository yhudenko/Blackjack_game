#include "Button.h"
#include "Game.h"

Button::Button(std::string buttonName, SDL_Rect* destinationRect) : BaseObject(destinationRect), name(buttonName)
{
	
}

Button::~Button()
{
	for (auto texture : textureLayers)
		texture->~Texture();
}

void Button::update()
{
	if (isHidden)
		return;
	isSelected = SDL_HasIntersection(objRect, Game::mousePos);
}

void Button::render()
{
	if (isHidden)
		return;
	if(textureLayers.empty())
		SDL_RenderDrawRect(Game::GetRenderer(), objRect);
	else
		for (auto texture : textureLayers)
			SDL_RenderCopy(Game::GetRenderer(), texture->texture, texture->sRect, objRect);
}

void Button::AddTexture(Texture* texture, bool bottomLayer)
{
	if (bottomLayer)
		textureLayers.push_front(texture);
	else
		textureLayers.push_back(texture);
}

