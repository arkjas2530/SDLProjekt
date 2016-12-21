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
		/*
		Tu trzeba zmieniæ, bo tracimy dwa najstarsze bity
		i przez to jakoœæ obrazka albo bêdzie kijowa albo 
		bêdziemy mieæ inne kolory. Dla procesora wygodniejsze
		jest przesuniêcie 
		*/
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

std::vector<Uint8> BytePacking6::decompression6bit(std::vector<Uint8>& buffor)
{
	unsigned int i = 0;
	result.reserve(buffor.size());

	while (i < buffor.size())
	{
		buffor[i] *= 4;
		depacking(buffor[i]);
		i++;
	}
	return result;
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

void BytePacking6::depacking(Uint8 color)
{
	Uint8 buf1 = color;
	if (freeSpace == 8)
	{
		result.push_back(color & 0b11111100);
		freeSpace = 2;
		buff = color << 6;
	}
	else if (freeSpace == 2)
	{
		//raczej dobrze
		buf1 >>= 2;
		buf1 &= 0b11111100;
		result.push_back(buff | buf1);
		freeSpace = 4;
		buff = color << 4;
	}
	else if (freeSpace == 4)
	{
		buf1 >>= 4;
		buf1 &= 0b11111100;
		result.push_back(buff | buf1);
		freeSpace = 8;
		buff = color << 2;
		result.push_back(buff);
	}
}


BytePacking6::~BytePacking6()
{
}
