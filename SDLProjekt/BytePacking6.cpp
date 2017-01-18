#include "BytePacking6.h"



BytePacking6::BytePacking6()
	:i(0),freeSpace(8),buff(0)
{
}

std::vector<Uint8> BytePacking6::compression6bit(std::vector<SDL_Color>& buffor,char colorchoice)
{
	size_t bufforEnd = buffor.size();
	result.reserve(3 * bufforEnd);
	
	int j = 0;

	if (colorchoice == '2')
	{
		int BW;
		while (j < bufforEnd)
		{
			BW = (buffor[j].r + buffor[j].g + buffor[j].b) / 3;
			buffor[j].r = BW;
			buffor[j].g = BW;
			buffor[j].b = BW;
			++j;
		}
	}


	while (i < bufforEnd)
	{		
		packing(buffor[i].r);
		packing(buffor[i].g);
		packing(buffor[i].b);
		++i;
	}

	if (freeSpace != 6)
	{
		result.push_back(buff);
	}
	return std::move(result);
}

std::vector<Uint8> BytePacking6::decompression6bit(std::vector<Uint8>& buffor)
{
	size_t bufforEnd = buffor.size();
	result.reserve(2*bufforEnd);
	
	while (i < bufforEnd)
	{
		depacking(buffor[i]);
		++i;
	}
	return std::move(result);
}

void BytePacking6::packing(const Uint8 &color)
{

	if (freeSpace == 8)
	{
		buff = color ;
		freeSpace = 2;
	}
	else if (freeSpace == 2)
	{
		buff |= color >> 6;
		result.push_back(buff);
		buff = color << 2;
		freeSpace = 4;
		
	}
	else if (freeSpace == 4 )
	{
		buff |= color >> 4;
		result.push_back(buff);
		buff = color << 4;
		freeSpace = 6;
		
	}
	else if (freeSpace == 6 )
	{
		buff |= color>>2;
		result.push_back(buff);
		freeSpace = 8;
	}

}

void BytePacking6::depacking(const Uint8 &color)
{
	Uint8 buf1 = color;

	if (freeSpace == 8)
	{
		buff = buf1 & 0xFC;
		result.push_back(buff); // 0b11111100
		freeSpace = 2;
		buff = color << 6;
	
	}
	else if (freeSpace == 2 )
	{
		buf1 >>= 2;
		buff = buff | buf1;
		result.push_back(buff & 0xFC);
		buff = 0;
		freeSpace = 4;
		buff = color << 4;
	
	}
	else if (freeSpace == 4 )
	{
		buf1 >>=4; //0b00000011
		buff = buff | buf1;
		result.push_back(buff &0xFC);
		freeSpace = 8;
		buff = color <<2;
		result.push_back(buff);
		
	}
}


BytePacking6::~BytePacking6()
{
	std::cout << " D-tor" << std::endl;
	
}
