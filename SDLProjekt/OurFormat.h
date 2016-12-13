#pragma once
#include <fstream>
#include <string>
#include <iostream>
struct outHeader
{
	int   headerSize;			// Dlugo�� w bitach info nag�owka
	int   width;			    // Szeroko�� obrazka w PIX
	int   height;				// Wysoko�� obrazka w PIX
	int   compression;			// Kompresja 0 Brak kompresji | 1 ByteRun  | 2 Huffman | 3 6-bit
	short isGreyScale;			// Czy skala szaro�ci
};
class OurFormat
{
	std::ofstream outFile;
public:
	OurFormat(std::string outName);
	void writeBin(const char*buff,int size);
	~OurFormat();

};

