#pragma once

#include <iostream>
#include "Deck.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };

	static SDL_Window* GetWindow();
	static SDL_Renderer* GetRenderer();

private:
	bool isRunning;
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	SDL_Texture* background;

	Deck* deck;

};

