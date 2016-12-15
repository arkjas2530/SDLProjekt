#pragma
#include<vector>
#include "OurFormat.h"
#include<SDL.h>

class BYTERUN
{

public:
	BYTERUN();
	std::vector<char> BYTERUN::compressBT(const std::vector<SDL_Color> &tab);
	std::vector<SDL_Color> BYTERUN::decompressBT(std::vector<char>buffor);//argument to nazwa pliku.. 
};
