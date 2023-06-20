#pragma once

#include "SDL_Engine.h"
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Hand.h"
#include "Button.h"
#include "Texture.h"
#include "Settings.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos = 0, int ypos = 0, int width = 100, int height = 100, Uint32 flags = 0);
	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning; };

private:
	bool isRunning = false;
	enum class gameStage
	{
		PRESTART = 0,
		DISTRIBUTION,
		TURNS,
		RESULTS,
		ROUNDEND
	}currentStage = gameStage::PRESTART;
	Texture* background = nullptr;
	Mix_Music* backgroundMusic = nullptr;
	Texture* currentTurnHeader = nullptr;
	Texture* currentTurn = nullptr;
	Settings* settings = nullptr;

	Deck* deck = nullptr;
	std::vector<Hand*> hands;
	int handIndex = 0;
	int playerIndex = -1;
	std::vector<Button*> buttons;

	void handSequence();
	void StartGame();
	void NextDistribution();
	void NextTurn();
	void changeCurrentTurnLabel();
	void CheckTurnEnded();
	void ShowResults();
	void ClearHands();

};

