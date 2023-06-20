#include "Button.h"
#include "SDL_Engine.h"
#include <iostream>
Mix_Chunk* Button::hoverChunk = nullptr;
Mix_Chunk* Button::pressChunk = nullptr;

Button::Button(std::string buttonName, SDL_Rect* destinationRect) : BaseObject(destinationRect), name(buttonName)
{
	if (!hoverChunk)
		hoverChunk = Mix_LoadWAV("data/hoverButton.wav");
	if(!pressChunk)
		pressChunk = Mix_LoadWAV("data/clickButton.wav");
}

Button::~Button()
{
	for (auto texture : textureLayers)
		delete texture;
	textureLayers.clear();
}

void Button::update()
{
	if (isHidden)
		return;
	bool oldSelected = isSelected;
	isSelected = SDL_HasIntersection(objRect, SDL_Engine::Instance()->mousePos);
	if (!oldSelected && isSelected)
		Mix_PlayChannel(-1, hoverChunk, 0);
}

void Button::render()
{
	if (isHidden)
		return;
	if (textureLayers.empty())
		SDL_RenderDrawRect(SDL_Engine::Instance()->GetRenderer(), objRect);
	else
		for (auto texture : textureLayers)
		{
			texture->render();
		}
			
}

void Button::AddTexture(Texture* texture)
{
	textureLayers.push_back(texture);
}

void Button::ButtonClicked()
{
	Mix_PlayChannel(-1, pressChunk, 0);
}

