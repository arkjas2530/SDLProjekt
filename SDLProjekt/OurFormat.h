#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <SDL.h>
#pragma pack(push,1)
struct outHeader
{
	int   headerSize;			// Dlugo�� w bitach info nag�owka
	int   width;			    // Szeroko�� obrazka w PIX
	int   height;				// Wysoko�� obrazka w PIX
	int   compression;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	int   capacityForTab;		// ile jest pikseli
	short isGreyScale;			// Czy skala szaro�ci	
};
#pragma pack(pop)
class OurFormat
{
	std::ofstream outFile;
	outHeader header;
	void writeBin(char *buff, int size);
	void generateHeader(const SDL_Surface *info, const int &size);
public:
	OurFormat(std::string outName);
	/*
	Full write to file with header and etc
	Args: SDL_Surface | Char buff, | size of Buff
	*/
	bool writeToFile(const SDL_Surface *info, char * buff, const int &size);
	void readBin(const char*buff, int size);
	void closeFile();
	~OurFormat();

};

