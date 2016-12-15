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

	void ProgramTekst();
	void KompresjaTekst();
	void DekompresjaTekst();
	void ByterunWelcome();

	void firstLevel();
	void ByteRun();
	bool levelCompress();
	bool levelDecompress();
	
	~Menu();
};

