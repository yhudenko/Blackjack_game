#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <map>
#include "Deck.h"
#include "Hand.h"
#include "Button.h"
#include "Texture.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos = 0, int ypos = 0, int width = 100, int height = 100, Uint32 flags = 0);
	void handleEvents();
	void update();
	void render();

	void StartGame();
	bool running() { return isRunning; };

	static SDL_Window* GetWindow();
	static SDL_Renderer* GetRenderer();
	static int animationFrameRate;
	static SDL_Rect* mousePos;

private:
	bool isRunning;
	enum class gameStage
	{
		PRESTART = 0,
		DISTRIBUTION,
		TURNS,
		RESULTS
	}currentStage = gameStage::PRESTART;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	Texture* background;

	Deck* deck;
	std::vector<Hand*> hands;
	std::vector<Button*> buttons;

};

