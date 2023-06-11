#include "Game.h"
#include "TextureManager.h"

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
	isRunning = false;
	background = nullptr;
	deck = nullptr;
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
{
	//Initialize the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL_Init Fail" << std::endl;
		return;
	}
	std::cout << "SDL Running..." << std::endl;

	//Create a window with the specified position, dimensions, and flags
	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window)
	{
		std::cout << "SDL_CreateWindow Fail" << std::endl;
		return;
	}
	std::cout << "Window created" << std::endl;

	//Create a 2D rendering context for a window
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "SDL_CreateRenderer Fail" << std::endl;
		return;
	}
	std::cout << "Renderer created" << std::endl;
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	background = TextureManager::LoadTexture("data/Background.jpg");

	deck = new Deck(1080, 100);

	isRunning = true;
}

void Game::handleEvents()
{
	SDL_Event currentEvent;
	SDL_PollEvent(&currentEvent);
	switch (currentEvent.type)
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}
}

void Game::update()
{
	deck->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, 0, 0);
	deck->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background);
	delete deck;
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

SDL_Window* Game::GetWindow()
{
	return window;
}

SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}

