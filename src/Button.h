#pragma once
#include <SDL.h>
#include <string>
#include "BaseObject.h"
#include "Texture.h"
#include <deque>

class Button : public BaseObject
{
public:
	Button(std::string buttonName, SDL_Rect* destinationRect);
	~Button();

	void update() override;
	void render() override;
	void AddTexture(Texture* texture, bool bottomLayer = false);

	bool isSelected = false;
	bool isHidden = false;
	std::string name = "";

protected:
	std::deque<Texture*> textureLayers;
};

