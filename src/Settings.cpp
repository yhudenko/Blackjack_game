#include "Settings.h"
#include "Deck.h"

Deck* Settings::deck = nullptr;

Settings::Settings()
{
	SDL_Rect* tempRect = nullptr;
	Button* tempButton = nullptr;

	tempRect = new SDL_Rect{ 70,10,150,50 };
	tempButton = new Button("ChangeBackSide", tempRect);
	tempButton->AddTexture(new Texture(tempRect, "Change back side", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);
}

Settings::~Settings()
{
	for (auto button : buttons)
		delete button;
	buttons.clear();
}

void Settings::mouseClicked()
{
	for (auto button : buttons)
	{
		if (button->isSelected)
		{
			if (button->name == "ChangeBackSide")
				if(deck) deck->ChangeCardBackSide();
		}
	}
}

void Settings::update()
{
	for (auto button : buttons)
		button->update();
}

void Settings::render()
{
	for (auto button : buttons)
		button->render();
}

void Settings::toggleVisibility()
{
	for (auto button : buttons)
		button->isHidden = !button->isHidden;
}
