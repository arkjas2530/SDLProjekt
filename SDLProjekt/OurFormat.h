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
		int   headerSize = 0;			// Dlugoœæ w bitach info nag³owka
		int   width = 0;			    // Szerokoœæ obrazka w PIX
		int   height = 0;				// Wysokoœæ obrazka w PIX
		short isGreyScale = 0;			// Czy skala szaroœci
		int   compression = 0;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	};
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);
	~OurFormat();
};

