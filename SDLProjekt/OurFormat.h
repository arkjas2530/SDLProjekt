#pragma once
#include <fstream>
#include <string>
#include <iostream>
struct outHeader
{
	int   headerSize;			// Dlugoœæ w bitach info nag³owka
	int   width;			    // Szerokoœæ obrazka w PIX
	int   height;				// Wysokoœæ obrazka w PIX
	int   compression;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	short isGreyScale;			// Czy skala szaroœci
};
class OurFormat
{
	std::ofstream outFile;
public:
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);
	~OurFormat();

};

