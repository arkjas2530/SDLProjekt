#include <iostream>
#include "SDLLoad.h"
#include"Byterun.h"
#include<fstream>

using namespace std;
int main(int argc, char* args[])
{
	ofstream file("outName", std::ofstream::binary | std::ofstream::trunc);
	//PóŸniej ma byæ wczytywanie nazyw z klawiatury
	std::string inName;	std::string outName;
	
	//Tworze obiekt klasy Byterun
	BYTERUN byterun;
	
	SDLLoad a("obrazek.bmp");
	std::vector<SDL_Color> buffor;
	int size;

	buffor = a.pixelArr(); //tablica zawierajaca struktury color z rgb


	file.open("test.bin", ofstream::in | ofstream::out | ofstream::binary);
	

	byterun.compressBT(buffor);

	//	a.saveToBMP(buffor);

	system("pause");
	return 0;
}