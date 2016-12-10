#include <iostream>
#include "SDLLoad.h"
#include"Byterun.h"
#include<fstream>

using namespace std;

int main(int argc, char* args[])
{
	ofstream file;
	//PóŸniej ma byæ wczytywanie nazyw z klawiatury
	std::string nazwa;
	std::string nazwa2;
	BYTERUN byterun;
	vector<int> pixtab;
	vector<int> tabtowrite;
	SDLLoad a("obrazek.bmp");
	std::vector<SDL_Color> buffor;
	int size;

	buffor = a.pixelArr(); //tablica zawierajaca struktury color z rgb
	size = buffor.size() * 3;

	file.open("test.bin", ofstream::in | ofstream::out | ofstream::binary);
	
	for (int i = 0; i < buffor.size(); i++)
	{
		pixtab.push_back(buffor[i].r);
		pixtab.push_back(buffor[i].g);
		pixtab.push_back(buffor[i].b);		
	}

	tabtowrite=byterun.compressBT(pixtab,file);

	

//	a.saveToBMP(buffor);

	system("pause");
	return 0;
}