#pragma once
#include<vector>
#include "OurFormat.h"
#include<SDL.h>

class BytePacking6
{
	unsigned int i;
	std::vector<Uint8> result;
	Uint8 buff;
	int freeSpace; //okreœla sekwencje pakowania
	void packing(const Uint8 &color);
	void depacking(const Uint8 &color);
public:
	BytePacking6();
	std::vector<Uint8> compression6bit(std::vector<SDL_Color> &buffor);
	std::vector<Uint8> decompression6bit(std::vector<Uint8> &buffor);
	~BytePacking6();
};

