#pragma
#include<vector>
#include<fstream>
#include "OurFormat.h"
#include<SDL.h>
#include<iostream>

class BYTERUN
{
	int n1;
	int n2;
	int i;
public:
	BYTERUN();
	int compressBT(std::vector<SDL_Color> tab);
};
