#pragma once
#include <vector>
#include "OurFormat.h"
#include "Leaf.h"
#include <cstdlib>
#include <algorithm>
#include <queue>

class HUFFMAN
{
	std::vector<unsigned int> freq;
	std::priority_queue < Leaf, std::vector < Leaf >,OperatorQueue> prioriQueue;

	void InsertIntoQueue(const Leaf &x);
	std::string huffmanCode[256];
	Leaf getElement();
public:
	HUFFMAN();
	void writeMap(OurFormat &out);
	void wypelnijSterte(); 

	std::shared_ptr<Leaf> TreeGenerating();

	
//	void wypiszWynik(std::shared_ptr<Leaf> korzen, std::vector<bool> kod);	// drukuje na ekran optymalne binarne kody prefiksowe
	void wypiszWynik(std::shared_ptr<Leaf> korzen, std::string kod);	// drukuje na ekran optymalne binarne kody prefiksowe

	void zwolnijPamiec(std::shared_ptr<Leaf> korzen);					// zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(std::vector<SDL_Color>& buffor);
	
	
	void huffmanCompress(const std::vector<SDL_Color>& buffor, OurFormat &out);
	~HUFFMAN();
};







