#include "Game.h"

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
int Game::animationFrameRate = 60;
SDL_Rect* Game::mousePos = nullptr;

Game::Game()
{
	isRunning = false;
	background = nullptr;
	deck = nullptr;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete background;
	delete deck;
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
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
	
	TTF_Init();
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	mousePos = new SDL_Rect{ 0,0,1,1 };
	background = new Texture("data/Background.jpg");
	
	Button* tempButton = nullptr;

	tempButton = new Button("Start", new SDL_Rect{ 540,100,200,50 });
	tempButton->AddTexture(new Texture(200, 50, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture("Start", 100, { 0, 0, 0, 255 }));
	buttons.push_back(tempButton);
	
	tempButton = new Button("Settings", new SDL_Rect{ 10,10,50,50 });
	tempButton->AddTexture(new Texture("data/settings.png", nullptr));
	buttons.push_back(tempButton);

	tempButton = new Button("ChangeBackSide", new SDL_Rect{ 70,10,150,50 });
	tempButton->AddTexture(new Texture("Change back side", 50, { 0,0,0,255 }));
	buttons.push_back(tempButton);

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
		break;
	case SDL_KEYDOWN:
		switch (currentEvent.key.keysym.sym)
		{
		case SDLK_UP:
			//Test
			break;
		}
	case SDL_MOUSEBUTTONUP:
		if(currentEvent.button.button == SDL_BUTTON_LEFT)
			for (auto button : buttons)
			{
				if (button->isSelected)
				{
					if (button->name == "Start" && currentStage == gameStage::PRESTART)
						StartGame();
					if (button->name == "ChangeBackSide")
						if(deck) deck->ChangeCardBackSide();
				}
			}
		break;
	default:
		break;
	}
}

void Game::update()
{
	SDL_GetMouseState(&mousePos->x, &mousePos->y);
	if(deck) deck->update();
	for (auto button : buttons)
		button->update();
	
}

void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background->texture, background->sRect, 0);
	if (deck) deck->render();
	for (auto button : buttons)
		button->render();

	SDL_RenderPresent(renderer);
}

void Game::StartGame()
{
	currentStage = gameStage::DISTRIBUTION;
	deck = new Deck(1080, 100);

}

SDL_Window* Game::GetWindow()
{
	return window;
}

SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}




