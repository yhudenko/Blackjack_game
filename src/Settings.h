#pragma once

#include "Button.h"
#include "Deck.h"
#include <vector>

class Deck;

class Settings
{
public:
	Settings();
	~Settings();

	void mouseClicked();
	void update();
	void render();
	void toggleVisibility();

	static Deck* deck;
private:
	std::vector<Button*> buttons;
};

