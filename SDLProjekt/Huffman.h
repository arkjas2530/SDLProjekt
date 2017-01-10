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

	int min;
	int max;
	std::vector<unsigned int> freq;
	std::priority_queue < std::shared_ptr<Leaf>, std::vector < std::shared_ptr<Leaf> >,OperatorQueue> prioriQueue;
	int freeSpace;
	std::vector<Uint8> result;
	Uint8 pack;
	bool canISave;
	void packing(Uint8 color);
	void InsertIntoQueue(std::shared_ptr<Leaf> x);
	std::string huffmanCode[256];
	std::shared_ptr<Leaf> getElement();
	void writeCodes(OurFormat &out);
	void makePile();
	std::shared_ptr<Leaf> TreeGenerating();
	void createCodes(std::shared_ptr<Leaf> korzen, std::string kod);	// drukuje na ekran optymalne binarne kody prefiksowe
	void zwolnijPamiec(std::shared_ptr<Leaf> korzen);					// zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(const std::vector<SDL_Color>& buffor);

public:
	HUFFMAN();
	void huffmanCompress(const std::vector<SDL_Color>& buffor);
	bool makeCompressedFile(OurFormat &out,SDL_Surface *headerInfo,int size);
	std::vector<uint8_t> huffmanDecompress(const unsigned int size, std::ifstream &in);

	std::map<std::string, unsigned char> getCodeMap(std::ifstream &in);
	//std::map<std::pair<int, unsigned char>, uint16_t> HUFFMAN::getCodeMap(std::ifstream & in); // dla testu !

	~HUFFMAN();
};







