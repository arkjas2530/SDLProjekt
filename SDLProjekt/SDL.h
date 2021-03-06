#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class LoadSaveExc :public std::exception
{
	std::string inName;
	std::string exc;
public:
	const char*what()
	{
		return exc.c_str();
	}
	void setName(std::string inName)
	{
		this->inName = inName;
	}
	void getName()
	{
		std::cout << "Entered name: " << inName;
	}
	void setMsg(std::string exc)
	{
		this->exc = exc;
	}
};

class SDL
{
	std::string nameBMP;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* gImage;
public:
	SDL(bool ifCompression = true, int width = 0,int height = 0);
	bool init(bool ifCompression = true, int width = 0, int height = 0);
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
	~SDL();
};

	