#include <iostream>
#include "SDLLoad.h"

using namespace std;

int main(int argc, char* args[])
{
	//P�niej ma by� wczytywanie nazyw z klawiatury
	std::string nazwa;
	SDLLoad a("obrazek.bmp");
	std::vector<SDL_Color> buffor;
	buffor = a.pixelArr();
	a.saveToBMP(buffor);

	system("pause");
	return 0;
}