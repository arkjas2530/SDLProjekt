#pragma
#include<vector>
#include "OurFormat.h"
#include<SDL.h>

class BYTERUN
{
	std::vector<char> result; //tablica skompresowanych danych
	std::vector<SDL_Color> decomResult;
public:
	
	BYTERUN();
	std::vector<char> BYTERUN::compressBT( std::vector<SDL_Color> &tab, char colorchoice);
	std::vector<SDL_Color> BYTERUN::decompressBT(const std::vector<char> &buffor);
	
};
