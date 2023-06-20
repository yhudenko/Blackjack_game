#pragma once
#include "BaseObject.h"
#include "Texture.h"
#include <deque>
#include <string>
#include <SDL_mixer.h>

class Button : public BaseObject
{
public:
	Button(std::string buttonName, SDL_Rect* destinationRect);
	~Button();

	void update() override;
	void render() override;

	void AddTexture(Texture* texture);
	void ButtonClicked();

	bool isSelected = false;
	bool isHidden = false;
	std::string name = "";

protected:
	std::deque<Texture*> textureLayers;
	
private:
	static Mix_Chunk* hoverChunk;
	static Mix_Chunk* pressChunk;
};

