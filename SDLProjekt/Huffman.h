#pragma once
#include <vector>
#include "OurFormat.h"
#include "Leaf.h"
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <bitset>

class HUFFMAN
{
	std::vector<unsigned int> freq;
	std::priority_queue < std::shared_ptr<Leaf>, std::vector < std::shared_ptr<Leaf> >,OperatorQueue> prioriQueue;
	int freeSpace;
	std::vector<Uint8> result;
	Uint8 pack;

	void packing(Uint8 color);
	void InsertIntoQueue(std::shared_ptr<Leaf> x);
	std::string huffmanCode[256];
	std::shared_ptr<Leaf> getElement();
public:
	HUFFMAN();
	void writeCodes(OurFormat &out);
	void wypelnijSterte(); 

	std::shared_ptr<Leaf> TreeGenerating();

	void wypiszWynik(std::shared_ptr<Leaf> korzen, std::string kod);	// drukuje na ekran optymalne binarne kody prefiksowe

	void zwolnijPamiec(std::shared_ptr<Leaf> korzen);					// zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(std::vector<SDL_Color>& buffor);
	void huffmanCompress(const std::vector<SDL_Color>& buffor, OurFormat &out);



	~HUFFMAN();
};







