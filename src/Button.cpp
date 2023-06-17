#include "Button.h"
#include "Game.h"

Button::Button(std::string buttonName, SDL_Rect* destinationRect) : BaseObject(destinationRect), name(buttonName)
{
	
}

Button::~Button()
{
	for (auto texture : textureLayers)
	{
		if (texture.first)
			delete texture.first;
		if (texture.second)
			delete texture.second;
	}
	textureLayers.clear();
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
			SDL_RenderCopy(Game::GetRenderer(), texture.first->texture, texture.first->sRect, (texture.second) ? texture.second : objRect);
}

void Button::AddBackground(int width, int height, SDL_Color color)
{
	std::pair<Texture*, SDL_Rect*> tempPair(new Texture(width, height, color) , nullptr);
	textureLayers.push_back(tempPair);
}

void Button::AddImage(const char* path, SDL_Rect* sRect, SDL_Rect* dRect)
{
	std::pair<Texture*, SDL_Rect*> tempPair(new Texture("data/settings.png"), nullptr);
	textureLayers.push_back(tempPair);
}


void Button::AddLabel(const char* text, SDL_Color color)
{
	SDL_Rect* dRect = new SDL_Rect{ objRect->x, objRect->y, objRect->w, objRect->h };
	Texture* tempTexture = new Texture(text, dRect, { 0, 0, 0, 255 });
	dRect->x = objRect->x + (objRect->w - dRect->w) / 2;
	dRect->y = objRect->y + (objRect->h - dRect->h) / 2;
	std::pair<Texture*, SDL_Rect*> tempPair(tempTexture, dRect);
	textureLayers.push_back(tempPair);
}

