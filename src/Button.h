#pragma once
#include <SDL.h>
#include "BaseObject.h"
#include "Texture.h"
#include <deque>
#include <string>

class Button : public BaseObject
{
public:
	Button(std::string buttonName, SDL_Rect* destinationRect);
	~Button();

	void update() override;
	void render() override;
	void AddBackground(int width, int height, SDL_Color color);
	void AddImage(const char* path, SDL_Rect* sRect = nullptr, SDL_Rect* dRect = nullptr);
	void AddLabel(const char* text, SDL_Color color);
	

	bool isSelected = false;
	bool isHidden = false;
	std::string name = "";

protected:
	std::deque<std::pair<Texture*, SDL_Rect*>> textureLayers;
};

