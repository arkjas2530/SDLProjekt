#pragma once
#include "SDLLoad.h"
#include"Byterun.h"
#include"OurFormat.h"
#include"BytePacking6.h"

#include "Huffman.h"

class Menu
{
	char choice;
	SDLLoad image;

	void programMenu();
	void compressMenu();
	void decompressMenu();
	void ByterunWelcome();
	void bytePackingWelcome();

	void ByteRun();
	void decompressByteRun();
	void bytePacking6();
	void decompressPacking6();

	void Huffman();
	
	bool levelCompress();
	bool levelDecompress();
public:
	Menu();
	void firstLevel();
	
	~Menu();
};

