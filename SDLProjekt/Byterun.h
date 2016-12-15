#pragma
#include<vector>
#include "OurFormat.h"
#include<SDL.h>

class BYTERUN
{
public:
	BYTERUN();
	int compressBT(std::vector<SDL_Color> &tab,OurFormat &file);
};
