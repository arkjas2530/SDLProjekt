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
	unsigned int i;
public:
	BYTERUN();
	std::vector<int> compressBT(std::vector<SDL_Color> tab);
};
