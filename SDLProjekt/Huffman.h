#pragma once
#include <vector>
#include "OurFormat.h"
#include "Leaf.h"
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>

class HUFFMAN
{
	std::vector<unsigned int> powtorzenia;
	std::priority_queue < Leaf, std::vector < Leaf >,OperatorQueue> kolejkaPriorytetowa;
	std::map<unsigned char, std::vector<bool>> codeMap;
	void wstaw(const Leaf &x);
	Leaf pobierzElement();

public:
	HUFFMAN();
	void wypelnijSterte(); 
	Leaf * algorytmHuffmana();
	std::map<unsigned char, std::vector<bool>> getCodeMap()
	{
		return codeMap;
	}
	
	void wypiszWynik(Leaf* korzen, std::vector<bool> kod);	// drukuje na ekran optymalne binarne kody prefiksowe
	void zwolnijPamiec(Leaf* korzen);					// zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(std::vector<SDL_Color>& buffor);
	
	
	void huffmanCompress(const std::vector<SDL_Color>& buffor, OurFormat &out);
	~HUFFMAN();
};







