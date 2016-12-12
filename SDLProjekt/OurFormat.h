#pragma once
#include <fstream>
#include <string>
#include <iostream>

class OurFormat
{
	std::ofstream outFile;
public:
	struct outHeader
	{
		int   headerSize = 0;			// Dlugo�� w bitach info nag�owka
		int   width = 0;			    // Szeroko�� obrazka w PIX
		int   height = 0;				// Wysoko�� obrazka w PIX
		short isGreyScale = 0;			// Czy skala szaro�ci
		int   compression = 0;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	};
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);
	~OurFormat();
};

