#include "Menu.h"



Menu::Menu()
	:choice(0)
{
	// zrobiæ ³adowanie obrazka wstêpnegos
}
void Menu::ProgramTekst()
{
	std::cout << "Witaj, w programie do Kompresji i Dekompresji danych" << std::endl;
	std::cout << "1.Kompresja" << std::endl;
	std::cout << "2.Dekompresja" << std::endl;
	std::cout << "3.Zakoncz program" << std::endl;
	std::cout << "Twoj Wybor ";
}
void Menu::KompresjaTekst()
{
	std::cout << "----------Kompresja Danych----------" << std::endl;
	std::cout << "1.ByteRun" << std::endl;
	std::cout << "2.Huffman" << std::endl;
	std::cout << "3.Upakowanie 6-bitowe" << std::endl;
	std::cout << "4.Powrot do menu glownego" << std::endl;
	std::cout << "Twoj wybor: ";
}
void Menu::DekompresjaTekst()
{
	std::cout << "---------Dekompresja Danych---------" << std::endl;
	std::cout << "1.ByteRun" << std::endl;
	std::cout << "2.Huffman" << std::endl;
	std::cout << "3.Upakowanie 6-bitowe" << std::endl;
	std::cout << "4.Do menu glownego" << std::endl;
	std::cout << "Twoj wybor: ";
}
void Menu::ByterunWelcome()
{
	std::cout << "----------ByteRun--------" << std::endl;
	std::cout << "Prosze czekac nastêpuje kompresja" << std::endl;
}

void Menu::firstLevel()
{
	while (true)
	{
		ProgramTekst();
		std::cin >> choice;
		switch (choice)
		{
		case '1':
		{
			
			levelCompress();
			break;
		}
		case '2':
		{
			levelDecompress();
			break;
		}
		case'3':
		{
			std::cout << "Koncze prace" << std::endl;
			exit(0);
		}
		case 0:
		{
			break;
		}
		default:
			std::cout << "Dokonales zlego wyboru, prosze wybrac jeszcze raz" << std::endl;
		}
	}

}

void Menu::ByteRun()
{
	std::vector<SDL_Color> buffor;
	std::vector<char> result;
	image.load("obrazek.bmp");
	buffor = image.pixelArr();		 //tablica zawierajaca struktury color z rgb
	BYTERUN byterun;
	result = byterun.compressBT(buffor);
	std::cout << result.size() <<std::endl <<buffor.size();
	system("pause");
	OurFormat out("out.asd");
	out.writeToFile(image.getBMPinfo(), reinterpret_cast<char*>(&result[0]), result.size()*sizeof(char));
}

bool Menu::levelCompress()
{
	
	KompresjaTekst();
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		ByterunWelcome();
		ByteRun();
		break;
	}
	case '2':
	{
		std::cout << "2 kompresja" << std::endl;
		break;
	}
	case '3':
	{
		std::cout << "2 kompresja" << std::endl;
		break;
	}
	case '4':
	{
		choice = 0;
		return true;
	}
	default:
		std::cout << "Zly wybor, wracam do Menu Glownego" << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
	return false;
}

bool Menu::levelDecompress()
{

	DekompresjaTekst();
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		std::cout << "BYTERUN" << std::endl;
		break;
	}
	case '2':
	{
		break;
	}
	case '3':
	{
		std::cout << "3 dekompresja" << std::endl;
		break;
	}
	case '4':
	{
		choice = 0;
		return true;
	}
	default:
		std::cout << "Zly wybor, wracam do Menu Glownego" << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
	return false;
}


Menu::~Menu()
{
}
