#pragma once
#include<vector>
#include "OurFormat.h"
#include<SDL.h>

class BytePacking6
{
	unsigned int i;
	std::vector<Uint8> result;
	Uint8 buff;
	int freeSpace; // sekwencja 2 4 6
public:
	BytePacking6();
	std::vector<Uint8> compression6bit(std::vector<SDL_Color> &buffor);
	std::vector<Uint8> decompression6bit(std::vector<Uint8> &buffor);
	void packing(Uint8 color);
	void depacking(Uint8 color);
	~BytePacking6();
};

