#pragma once
#include "SDLLoad.h"
#include"Byterun.h"
#include"OurFormat.h"

class Menu
{
	char choice;
	SDLLoad image;

	void programMenu();
	void compressMenu();
	void decompressMenu();
	void ByterunWelcome();

	void ByteRun();
	void decompressByteRun();
	bool levelCompress();
	bool levelDecompress();
public:
	Menu();
	void firstLevel();
	
	~Menu();
};

