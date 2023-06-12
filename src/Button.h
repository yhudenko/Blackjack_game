#pragma once
#include <SDL.h>
#include <string>

class Button
{
public:
	Button(std::string buttonName, SDL_Rect* destinationRect, SDL_Texture* buttonTexture = nullptr, SDL_Rect* sourceRect = nullptr);
	~Button();

	void update();
	void render();

	bool isSelected = false;
	bool isHidden = false;
	std::string name = "";

protected:
	SDL_Texture* texture;
	SDL_Rect* sRect;
	SDL_Rect* dRect;
};

