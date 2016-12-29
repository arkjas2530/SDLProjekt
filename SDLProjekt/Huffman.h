#pragma once
#include<vector>
#include "OurFormat.h"
#include "Leaf.h"
#include<cstdlib>
#include <algorithm>
#include <queue>


class HUFFMAN
{
	std::vector<unsigned int> powtorzenia;
	std::priority_queue < Leaf, std::vector < Leaf >,OperatorQueue > kolejkaPriorytetowa;
	std::vector<Leaf> heap;
public:
	void wypelnijSterte(); 
	Leaf * algorytmHuffmana();
	HUFFMAN();
	void wypiszWynik(Leaf* korzen, std::string kod); // drukuje na ekran optymalne binarne kody prefiksowe
	void zwolnijPamiec(Leaf* korzen); // zwalnia pamiec (drzewo)
	void zliczaniePowtorzen(std::vector<SDL_Color>& buffor);
	Leaf pobierzElement();
	void wstaw(const Leaf &x);
	~HUFFMAN();
};







