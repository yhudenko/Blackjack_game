#include "src/Game.h"


int main(int argc, char* args[])
{
	const int FPS = 60;
	const int targetFrameTime = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;


	Game* game = new Game();
	game->init("Blackjack Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (targetFrameTime > frameTime)
			SDL_Delay(targetFrameTime - frameTime);
	}

	delete game;

	return 0;
}


