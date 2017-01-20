#pragma once
#include <vector>
#include "OurFormat.h"
#include "Leaf.h"
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>
#include <bitset>


class HUFFMAN
{


	std::vector<unsigned int> freq;
	std::priority_queue < std::shared_ptr<Leaf>, std::vector < std::shared_ptr<Leaf> >,OperatorQueue> prioriQueue;

	std::vector<Uint8> result;
	
	size_t min;
	int freeSpace;
	int saved;
	Uint8 pack;
	uint16_t depack;

	bool canISave;
	
	std::map<uint16_t, unsigned char> codeMap;
	std::string huffmanCode[253];

	void packing(Uint8 color);
	void depacking(uint8_t coded);

	void InsertIntoQueue(std::shared_ptr<Leaf> x);
	std::shared_ptr<Leaf> getElement();
	void writeCodes(OurFormat &out);
	void makePile();
	std::shared_ptr<Leaf> TreeGenerating();
	void createCodes(std::shared_ptr<Leaf> korzen, std::string kod);	// drukuje na ekran optymalne binarne kody prefiksowe
	void zwolnijPamiec(std::shared_ptr<Leaf> korzen);					// zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(const std::vector<SDL_Color>& buffor);

public:
	HUFFMAN();
	void huffmanCompress(std::vector<SDL_Color>& buffor,char colorchoice);
	bool makeCompressedFile(OurFormat &out,SDL_Surface *headerInfo,int size);
	std::vector<uint8_t> huffmanDecompress(const unsigned int size, std::ifstream &in);

	//std::map<std::string, unsigned char> getCodeMap(std::ifstream &in);
	void HUFFMAN::getCodeMap(std::ifstream & in); // dla testu ! DZIALA !

	~HUFFMAN();
};







