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

	void AddTexture(Texture* texture);	

	bool isSelected = false;
	bool isHidden = false;
	std::string name = "";

protected:
	std::deque<Texture*> textureLayers;
};

