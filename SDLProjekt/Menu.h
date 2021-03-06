#pragma once
#include"SDL.h"
#include"Byterun.h"
#include"OurFormat.h"
#include"BytePacking6.h"
#include "Huffman.h"


class Menu
{
	char choice;
	char colorchoice;
	std::string name;
	SDL image;
	std::ifstream file;

	void programMenu();
	void colorMenu(); //kolorowy obrazek albo czarno-bialy
	void compressMenu();
	void decompressMenu();
	void ByterunWelcome();
	void bytePackingWelcome();
	void huffmanWelcome();

	void loadingImage();
	void decompressionError();

	void ByteRun(char colorchoice);
	void decompressByteRun();
	
	void bytePacking6(char colorchoice);
	void decompressPacking6();

	void Huffman(char colorchoice);
	void decompressHuffman();
	
	bool levelCompress();
	bool levelDecompress();
	void changebuffor(std::vector<SDL_Color> &buffor);
public:
	Menu();
	void firstLevel();
	
	~Menu();
};

