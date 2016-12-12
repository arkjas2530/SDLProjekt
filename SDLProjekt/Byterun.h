#pragma
#include<vector>
#include<fstream>
#include<SDL.h>

class BYTERUN
{
	int n1;
	int n2;
	int i;
	OurFormat::outHeader header;

public:
	BYTERUN();
	void compressBT(std::vector<SDL_Color> tab);

};
