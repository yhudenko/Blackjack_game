#pragma once

#include "Button.h"
#include "Deck.h"
#include <vector>

class Deck;

class Settings : public Button
{
public:
	Settings(std::string buttonName, SDL_Rect* destinationRect);
	~Settings();

	void mouseClicked();
	void update();
	void render();
	void toggleVisibility();

	static Deck* deck;
private:
	bool isOpen = false;
	std::vector<Button*> buttons;
	std::vector<Texture*> labels;

	int chunkVolume = 50;
	SDL_Rect chunkVolumeRect = SDL_Rect{ 220,70,30,30 };
	Texture* chunkVolumeLabel = nullptr;
	int musicVolume = 50;
	SDL_Rect musicVolumeRect = SDL_Rect{ 220,120,30,30 };
	Texture* musicVolumeLabel = nullptr;

	void updateChunkVolumeLabel();
	void updateMusicVolumeLabel();
};

