#pragma once
#include "SDLLoad.h"
#include"Byterun.h"
#include"OurFormat.h"

class Menu
{
	char choice;
	SDLLoad image;
public:
	Menu();

	//text menu 
	void programMenu();
	void compressMenu();
	void decompressMenu();
	void ByterunWelcome();

	void firstLevel();
	void ByteRun();
	void decompressByteRun();
	bool levelCompress();
	bool levelDecompress();
	
	~Menu();
};

