#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

class SDLLoad
{
	std::string nameBMP; // moze zamiast tego const char ?


	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* gImage;
public:
	SDLLoad(std::string);
	bool init();
	bool load();
	~SDLLoad();
};

