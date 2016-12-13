
#include "SDLLoad.h"
#include"Byterun.h"
#include"OurFormat.h"

#include<fstream>
#include <iostream>

using namespace std;
/*
Zrobiæ klase Menu
*/
void ProgramTekst()
{
	cout << "Witaj, w programie do Kompresji i Dekompresji danych" << endl;
	cout << "1.Kompresja" << endl;
	cout << "2.Dekompresja" << endl;
	cout << "3.Zakoñcz program" << endl;
	cout << "Twoj Wybor ";
}
void KompresjaTekst()
{
	cout << "----------Kompresja Danych----------" << endl;
	cout << "1.ByteRun" << endl;
	cout << "2.Huffman" << endl;
	cout << "3.Upakowanie 6-bitowe" << endl;
	cout << "Twój wybór: ";
}
void DekompresjaTekst()
{
	cout << "---------Dekompresja Danych---------" << endl;
	cout << "1.ByteRun" << endl;
	cout << "2.Huffman" << endl;
	cout << "3.Upakowanie 6-bitowe" << endl;
	cout << "4.Do menu g³ownego" << endl;
	cout << "Twój wybór: ";
}
void ByterunWelcome()
{
	cout << "----------ByteRun--------" << endl;
	cout << "Prosze czekaæ nastêpujê kompresja" << endl;
}
/*
Spróbowaæ za pomoc¹ takiej funkcji wype³niaæ strukture header
*/
void HeaderFilling(SDL_Surface* image)
{

}
void menu()
{
	char choice;

	SDLLoad a("obrazek.bmp");
	std::vector<SDL_Color> buffor;
	buffor = a.pixelArr(); //tablica zawierajaca struktury color z rgb

	while (true)
	{
		ProgramTekst();
		cin >> choice;
		SDL_Surface* info = a.getBMPinfo();
		switch (choice)
		{
		case '1':
		{
			while (true)
			{
				KompresjaTekst();
				cin >> choice;
				switch (choice)
				{
				case '1':
				{
					ByterunWelcome();
				
					BYTERUN byterun;
					outHeader header;
					std::vector<int> pixels;
					header.compression = 1;
					header.headerSize = sizeof(header);
					header.isGreyScale = 0;
					header.height = info->h;
					header.width = info->w;
					pixels = byterun.compressBT(buffor);
					header.capacityForTab = pixels.capacity();

					OurFormat out("outfile.xyz");
					out.writeBin(reinterpret_cast<const char*>(&header), sizeof(header));
					out.writeBin(reinterpret_cast<const char*>(&pixels), pixels.capacity());
					break;
				}
				case '2':
					break;
				case '3':
					break;
				default:
					break;
				}
			}
			break;
		}
		case '2':
		{
			while (true)
			{
				DekompresjaTekst();
				cin >> choice;
				switch (choice)
				{
				case '1':
				{
					break;
				}
				case '2':
					break;
				case '3':
					break;
				default:
					break;
				}
			}
			break;
		}
		case 3:
			break;
		}
	}
}
int main(int argc, char* args[])
{
	//PóŸniej ma byæ wczytywanie nazyw z klawiatury
	std::string inName;	std::string outName;
	outHeader a;
	cout << sizeof(a);
	menu();
	system("pause");
	return 0;
}