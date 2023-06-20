#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class SDL_Engine
{
public:
    SDL_Engine(SDL_Engine& other) = delete;
    ~SDL_Engine();
    void operator=(const SDL_Engine&) = delete;

    static SDL_Engine* Instance();
    void CreateWindow(const char* title, int xpos = 0, int ypos = 0, int width = 100, int height = 100, Uint32 flags = 0);

    bool Running();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();
    void UpdateMousePos();

    const int animationFrameRate = 60;
    SDL_Rect* mousePos = nullptr;
	
protected:
    bool isRunning = false;
    SDL_Engine();
    static SDL_Engine* engine;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
   
};

