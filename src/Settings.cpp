#include "Settings.h"
#include <string>

Deck* Settings::deck = nullptr;

Settings::Settings(std::string buttonName, SDL_Rect* destinationRect) : Button(buttonName, destinationRect)
{
	AddTexture(new Texture(destinationRect, "data/settings.png"));

	SDL_Rect* tempRect = nullptr;
	Button* tempButton = nullptr;

	tempRect = new SDL_Rect{ 70,10,150,50 };
	tempButton = new Button("ChangeBackSide", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "Change back side", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	tempRect = new SDL_Rect{ 10,70,150,30 };
	labels.push_back(new Texture(tempRect, "Chunk volume", SDL_Color{ 0,0,0 }));
	
	tempRect = new SDL_Rect{ 170,70,30,30 };
	tempButton = new Button("ChunkVolume-", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "-", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	updateChunkVolumeLabel();

	tempRect = new SDL_Rect{ 260,70,30,30 };
	tempButton = new Button("ChunkVolume+", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "+", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	tempRect = new SDL_Rect{ 10,120,150,30 };
	labels.push_back(new Texture(tempRect, "Music volume", SDL_Color{ 0,0,0 }));

	tempRect = new SDL_Rect{ 170,120,30,30 };
	tempButton = new Button("MusicVolume-", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "-", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);

	updateMusicVolumeLabel();

	tempRect = new SDL_Rect{ 260,120,30,30 };
	tempButton = new Button("MusicVolume+", tempRect);
	tempButton->AddTexture(new Texture(tempRect, SDL_Color{ 255,229,204 }));
	tempButton->AddTexture(new Texture(tempRect, "+", SDL_Color{ 0,0,0 }));
	buttons.push_back(tempButton);
}

Settings::~Settings()
{
	for (auto button : buttons)
		delete button;
	buttons.clear();
	for (auto label : labels)
		delete label;
	labels.clear();
	delete chunkVolumeLabel;
	delete musicVolumeLabel;
}

void Settings::mouseClicked()
{
	if (isSelected)
		isOpen = !isOpen;
	if (!isOpen)
		return;
	for (auto button : buttons)
	{
		if (button->isSelected)
		{
			if (button->name == "ChangeBackSide")
				if (deck) deck->ChangeCardBackSide();
			if (button->name == "ChunkVolume-")
				if (chunkVolume > 0)
				{
					chunkVolume -= 10;
					updateChunkVolumeLabel();
				}
			if (button->name == "ChunkVolume+")
				if (chunkVolume < 100)
				{
					chunkVolume += 10;
					updateChunkVolumeLabel();
				}
			if (button->name == "MusicVolume-")
				if (musicVolume > 0)
				{
					musicVolume -= 10;
					updateMusicVolumeLabel();
				}
			if (button->name == "MusicVolume+")
				if (musicVolume < 100)
				{
					musicVolume += 10;
					updateMusicVolumeLabel();
				}
		}
	}
}

void Settings::update()
{
	Button::update();
	if (!isOpen)
		return;
	for (auto button : buttons)
		button->update();
}

void Settings::render()
{
	Button::render();
	if (!isOpen)
		return;
	for (auto button : buttons)
		button->render();
	for (auto label : labels)
		label->render();
	if (chunkVolumeLabel) chunkVolumeLabel->render();
	if (musicVolumeLabel) musicVolumeLabel->render();
}

void Settings::toggleVisibility()
{
	for (auto button : buttons)
		button->isHidden = !button->isHidden;
}

void Settings::updateChunkVolumeLabel()
{
	delete chunkVolumeLabel;
	chunkVolumeLabel = new Texture(&chunkVolumeRect, std::to_string(chunkVolume).c_str(), SDL_Color{ 0,0,0 });
	Mix_Volume(-1, static_cast<int>(1.28f * chunkVolume));
}

void Settings::updateMusicVolumeLabel()
{
	delete musicVolumeLabel;
	musicVolumeLabel = new Texture(&musicVolumeRect, std::to_string(musicVolume).c_str(), SDL_Color{ 0,0,0 });
	Mix_VolumeMusic(static_cast<int>(1.28f * musicVolume));
}

