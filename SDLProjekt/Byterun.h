#pragma
#include<vector>
#include<fstream>
#include "OurFormat.h"
#include<SDL.h>
#include<iostream>

class BYTERUN
{
public:
	BYTERUN();
	int compressBT(const std::vector<SDL_Color> &tab);
};
