#include "BytePacking6.h"



BytePacking6::BytePacking6()
	:i(0),freeSpace(8),buff(0)
{
}

std::vector<Uint8> BytePacking6::compression6bit(std::vector<SDL_Color>& buffor)
{
	result.reserve(3 * buffor.size());

	while (i < buffor.size())
	{
		buffor[i].r /= 4;
		buffor[i].g /= 4;
		buffor[i].b /= 4;

		packing(buffor[i].r);
		packing(buffor[i].g);
		packing(buffor[i].b);
		++i;
	}
	return std::move(result);
}

std::vector<SDL_Color> BytePacking6::decompression6bit(std::vector<Uint8>& buffor)
{
	return std::vector<SDL_Color>();
}

void BytePacking6::packing(Uint8 color)
{
	if (freeSpace == 8)
	{
		buff = color << 2;
		freeSpace = 2;
	}
	else if (freeSpace == 2)
	{
		buff |= color >> 4;
		result.push_back(buff);
		buff = color << 4;
		freeSpace = 4;
	}
	else if (freeSpace == 4)
	{
		buff |= color >> 2;
		result.push_back(buff);
		buff = color << 6;
		freeSpace = 6;
	}
	else if (freeSpace == 6)
	{
		buff |= color;
		result.push_back(buff);
		freeSpace = 8;
	}
}


BytePacking6::~BytePacking6()
{
}
