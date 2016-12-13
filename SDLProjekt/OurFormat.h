#pragma once
#include <fstream>
#include <string>
#include <iostream>
#pragma pack(push,1)
struct outHeader
{
	int   headerSize;			// Dlugoœæ w bitach info nag³owka
	int   width;			    // Szerokoœæ obrazka w PIX
	int   height;				// Wysokoœæ obrazka w PIX
	int   compression;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	int   capacityForTab;		// ile jest pikseli
	short isGreyScale;			// Czy skala szaroœci	
};
#pragma pack(pop)
class OurFormat
{
	std::ofstream outFile;
public:
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);

	~OurFormat();

};

