#include "SDL_Engine.h"
#include <iostream>

SDL_Engine* SDL_Engine::engine = nullptr;

SDL_Engine::~SDL_Engine()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	delete mousePos;
	mousePos = nullptr;
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	std::cout << "Engine deleted" << std::endl;
}

SDL_Engine* SDL_Engine::Instance()
{
	if (engine == nullptr)
		engine = new SDL_Engine();
	return engine;
}

void SDL_Engine::CreateWindow(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
{
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
	mousePos = new SDL_Rect{ 0,0,1,1 };
}

bool SDL_Engine::Running()
{
	return isRunning;
}

SDL_Window* SDL_Engine::GetWindow()
{
	return window;
}

SDL_Renderer* SDL_Engine::GetRenderer()
{
	return renderer;
}

void SDL_Engine::UpdateMousePos()
{
	SDL_GetMouseState(&mousePos->x, &mousePos->y);
}


SDL_Engine::SDL_Engine()
{
	//Initialize the SDL library
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL_Init Fail" << std::endl;
		return;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Linear texture filtering not enabled!" << std::endl;
		return;
	}

	//Initialize PNG loading
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cout << "SDL_image initialize Fail" << std::endl;
		return;
	}

	//Initialize TTF_Init
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init initialize Fail" << std::endl;
		return;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer initialize Fail" << std::endl;
		return;
	}

	std::cout << "SDL Engine Running..." << std::endl;
	isRunning = true;
}
