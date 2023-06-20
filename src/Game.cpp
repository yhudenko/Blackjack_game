#include "Game.h"
#include "Player.h"
#include "Bot.h"
#include "Dealer.h"

Game::Game()
{

}

Game::~Game()
{
	delete background;
	background = nullptr;
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = nullptr;
	delete currentTurn;
	currentTurn = nullptr;
	delete deck;
	deck = nullptr;
	for (auto button : buttons)
		delete button;
	buttons.clear();

	delete SDL_Engine::Instance();
	std::cout << "Game cleaned" << std::endl;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
{
	SDL_Engine::Instance()->CreateWindow(title, xpos, ypos, width, height, flags);
	if (SDL_Engine::Instance()->Running() == false)
	{
		isRunning = false;
		return;
	}
	
	background = new Texture(nullptr, "data/Background.jpg");
	backgroundMusic = Mix_LoadMUS("data/BackgroundMusic.mp3");
	Mix_PlayMusic(backgroundMusic, -1);
	
	SDL_Rect* tempRect = nullptr;
	Button* tempButton = nullptr;
	
	tempRect = new SDL_Rect{ 540,100,200,100 };
	tempButton = new Button("Start", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "Start", SDL_Color{ 0, 0, 0}, 0.6f));
	buttons.push_back(tempButton);
	
	tempRect = new SDL_Rect{ 10,10,50,50 };
	settings = new Settings("Settings", tempRect);

	tempRect = new SDL_Rect{ 1080,500,100,50 };
	tempButton = new Button("Hit", tempRect);
	tempButton->AddTexture(new Texture(tempRect, "Hit", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	tempRect = new SDL_Rect{ 1080,550,100,50 };
	tempButton = new Button("Stand", tempRect);
	tempButton->AddTexture(new Texture(tempRect, "Stand", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	tempRect = new SDL_Rect{ 1080,600,100,50 };
	tempButton = new Button("Bet", tempRect);
	tempButton->AddTexture(new Texture(tempRect, "Bet 100$", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	tempButton = nullptr;
	

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
	case SDL_MOUSEBUTTONUP:
		if (currentEvent.button.button == SDL_BUTTON_LEFT)
		{
			if (settings) settings->mouseClicked();
			for (auto button : buttons)
			{
				if (button->isSelected)
				{
					button->ButtonClicked();
					if (button->name == "Start" && currentStage == gameStage::PRESTART)
						StartGame();
					if (button->name == "Settings")
						settings->toggleVisibility();
					if (button->name == "Hit" && handIndex == playerIndex)
						hands.at(playerIndex)->Hit(deck);
					if (button->name == "Stand" && handIndex == playerIndex)
						hands.at(playerIndex)->Stand();
					if (button->name == "Bet" && handIndex == playerIndex)
						hands.at(playerIndex)->BetChip();
					if (button->name == "Continue")
					{
						if (buttons.back()->name == "Continue")
							buttons.pop_back();
						delete button;

						ClearHands();
						currentStage = gameStage::DISTRIBUTION;
						handIndex = 0;
						changeCurrentTurnLabel();
						hands.at(handIndex)->Distribution(deck);
					}
					if(button->name == "Restart")
					{
						if (buttons.back()->name == "Restart")
							buttons.pop_back();
						delete button;

						ClearHands();
						deck->Clear();
						deck->CreateDeck();
						hands.at(handIndex)->getChips(10);

						currentStage = gameStage::DISTRIBUTION;
						handIndex = 0;
						changeCurrentTurnLabel();
						hands.at(handIndex)->Distribution(deck);
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	SDL_Engine::Instance()->UpdateMousePos();
	
	if (settings) settings->update();

	if(deck) deck->update();

	if (currentStage != gameStage::PRESTART)
		handSequence();
	
	for (auto button : buttons)
		button->update();
	
}

void Game::render()
{
	SDL_RenderClear(SDL_Engine::Instance()->GetRenderer());

	background->render();
	if (deck) deck->render();

	if (settings) settings->render();

	for (auto hand : hands)
		hand->render();

	for (auto button : buttons)
		button->render();
	
	if (currentTurnHeader) currentTurnHeader->render();
	if(currentTurn) currentTurn->render(1080, 275);
	SDL_RenderPresent(SDL_Engine::Instance()->GetRenderer());
}

void Game::handSequence()
{
	hands.at(handIndex)->update();
	if (!hands.at(handIndex)->somethingMoving)
	{
		switch (currentStage)
		{
		case Game::gameStage::DISTRIBUTION:
			NextDistribution();
			break;
		case Game::gameStage::TURNS:
			if (hands.at(handIndex)->endTurn)
				NextTurn();
			CheckTurnEnded();
			break;
		case Game::gameStage::RESULTS:
			ShowResults();
			break;
		default:
			break;
		}
	}
	
}

void Game::StartGame()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
		if ((*it)->name == "Start")
		{
			delete *it;
			buttons.erase(it);
			break;
		}

	hands.push_back(new Bot(new SDL_Rect{ 100,300,100,100 }, "Jack BOT"));
	playerIndex = 1;
	hands.push_back(new Player(new SDL_Rect{ 350,300,100,100 }, "Player"));
	hands.push_back(new Dealer(new SDL_Rect{ 700,100,100,100 }, "Dealer"));
			
	currentStage = gameStage::DISTRIBUTION;
	deck = new Deck(1080, 100);
	Settings::deck = deck;
	currentTurnHeader = new Texture(new SDL_Rect{ 1080,250,100,50 }, "Wating for:", SDL_Color{ 0,0,0 });
	changeCurrentTurnLabel();
	hands.at(handIndex)->Distribution(deck);
}

void Game::NextDistribution()
{
	hands.at(handIndex)->endTurn = false;
	if ((handIndex + 1) < static_cast<int>(hands.size()))
		++handIndex;
	else
		handIndex = 0;

	changeCurrentTurnLabel();
	if (hands.at(handIndex)->Distribution(deck))
	{
		currentStage = gameStage::TURNS;
		hands.at(handIndex)->endTurn = true;
	}
}

void Game::NextTurn()
{
	hands.at(handIndex)->endTurn = false;
	if (handIndex + 1 < static_cast<int>(hands.size()))
		++handIndex;
	else
		handIndex = 0;
	changeCurrentTurnLabel();
	if (hands.at(handIndex)->status == HandStatus::PLAYING)
		hands.at(handIndex)->Turn(deck, hands.back());
	else
		hands.at(handIndex)->endTurn = true;
}

void Game::changeCurrentTurnLabel()
{
	currentTurn = hands.at(handIndex)->getNameLabel();
}

void Game::CheckTurnEnded()
{
	bool playing = false;
	for (auto hand : hands)
		playing = playing || hand->status == HandStatus::PLAYING;
	if (!playing)
	{
		currentStage = gameStage::RESULTS;
		hands.back()->Results();
		hands.at(handIndex)->endTurn = true;
		handIndex = 0;
		changeCurrentTurnLabel();
		int dealerValue = hands.back()->calculateValue();
		hands.at(handIndex)->Results(dealerValue);
	}
}

void Game::ShowResults()
{
	hands.at(handIndex)->endTurn = false;
	if (handIndex + 1 < static_cast<int>(hands.size() - 1))
	{
		++handIndex;
		changeCurrentTurnLabel();
		int dealerValue = hands.back()->calculateValue();
		hands.at(handIndex)->Results(dealerValue);
	}
	else
	{
		hands.at(handIndex)->endTurn = true;
		currentStage = gameStage::ROUNDEND;
		handIndex = playerIndex;

		SDL_Rect* tempRect = nullptr;
		Button* tempButton = nullptr;
		
		bool canContinue = true;
		for (auto hand : hands)
			canContinue &= hand->CanContinue();
		if (canContinue)
		{
			tempRect = new SDL_Rect{ 700,400,200,100 };
			tempButton = new Button("Continue", tempRect);
			tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
			tempButton->AddTexture(new Texture(tempRect, "Continue", SDL_Color{ 0,0,0 }));
			buttons.push_back(tempButton);
		}
		else
		{
			tempRect = new SDL_Rect{ 700,400,200,100 };
			tempButton = new Button("Restart", tempRect);
			tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
			tempButton->AddTexture(new Texture(tempRect, "Restart", SDL_Color{ 0,0,0 }));
			buttons.push_back(tempButton);
		}
	}		
}

void Game::ClearHands()
{
	for (auto hand : hands)
		hand->clear();
}




