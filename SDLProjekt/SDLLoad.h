#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class SDLLoad
{
	std::string nameBMP;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* gImage;
public:
	SDLLoad();
	bool init();
	bool load(std::string _name);
	SDL_Surface* getBMPinfo()
	{
		return gImage;
	}
	std::vector<SDL_Color> pixelArr();
	SDL_Color getPixel(int x, int y,SDL_Surface* image);
	
	void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B,SDL_Surface *image);
	void saveToBMP(const std::vector<SDL_Color> &buffor);
	void saveToBMP(const std::vector<Uint8> &buffor);
	~SDLLoad();
};

	