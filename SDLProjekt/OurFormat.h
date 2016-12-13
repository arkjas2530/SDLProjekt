#pragma once
#include <fstream>
#include <string>
#include <iostream>
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
public:
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);

	~OurFormat();

};

