#include "Menu.h"



Menu::Menu()
	:choice(0)
{
	// zrobić ładowanie obrazka wstępnego
}
void Menu::programMenu()
{
	std::cout << "Witaj, w programie do Kompresji i Dekompresji danych" << std::endl;
	std::cout << "1.Kompresja" << std::endl;
	std::cout << "2.Dekompresja" << std::endl;
	std::cout << "3.Zakoncz program" << std::endl;
	std::cout << "Twoj Wybor ";
}
void Menu::compressMenu()
{
	std::cout << "----------Kompresja Danych----------" << std::endl;
	std::cout << "1.ByteRun" << std::endl;
	std::cout << "2.Huffman" << std::endl;
	std::cout << "3.Upakowanie 6-bitowe" << std::endl;
	std::cout << "4.Powrot do menu glownego" << std::endl;
	std::cout << "Twoj wybor: ";
}
void Menu::decompressMenu()
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
	std::cout << "Prosze czekac nastepuje kompresja" << std::endl;
}

void Menu::bytePackingWelcome()
{
	std::cout << "-------Upakowanie 6 bitowe-----" << std::endl;
	std::cout << "Prosze czekac nastepuje kompresja" << std::endl;
}


void Menu::firstLevel()
{
	while (true)
	{
		system("cls");
		programMenu();
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
	std::vector<SDL_Color> buffor;	//tablica zawierajaca struktury color z rgb
	std::vector<char> result;		//skompresowana tablica
	BYTERUN byterun;

	image.load("obrazek.bmp");	
	buffor = image.pixelArr();		 

	
	result = byterun.compressBT(buffor); // wywola sie tylko konstruktor przenoszenia przez std move
	std::cout << std::endl << "Kompresja zakończona sukcesem!" << std::endl;
	system("pause");  

	OurFormat out("outB.asd"); //utworzenie pliku ze skompresowanymi danymi
	out.writeToFile(image.getBMPinfo(), reinterpret_cast<char*>(&result[0]), result.size()*sizeof(char));//zapisanie naglowka i skompresowanej tablicy
}

void Menu::decompressByteRun()
{
	BYTERUN DC;
	outHeader readHeader; //stworzenie obiektu do odczytu naglowka
	std::ifstream readFile;
	std::vector<char> buffor; //skompresowana tab
	std::vector<SDL_Color> decompressbuffor; //zdekompresowana tab

	readFile.open("outB.asd", std::ios_base::binary);
	readFile.read(reinterpret_cast<char*>(&readHeader), sizeof(readHeader));
	readFile.seekg(22, std::ios_base::beg); // ustawienie sie na bajcie od ktorego zaczyna sie skompresowana tablica

	
	buffor.resize(readHeader.capacityForTab);
	readFile.read(reinterpret_cast<char*>(&buffor[0]), readHeader.capacityForTab);

	decompressbuffor = DC.decompressBT(buffor);
	std::cout << std::endl << "Dekompresja zakończona sukcesem!" << std::endl;
	system("pause");

	image.saveToBMP(decompressbuffor); //zapis obrazka skompresoeanego
}

void Menu::bytePacking6()
{
	std::vector<SDL_Color> buffor;	//tablica zawierajaca struktury color z rgb
	std::vector<Uint8> result;		//skompresowana tablica

	image.load("obrazek.bmp");
	buffor = image.pixelArr();
	BytePacking6 pack;
	result = pack.compression6bit(buffor);
	std::cout << std::endl << "Kompresja zakończona sukcesem!" << std::endl;
	system("pause");

	OurFormat out("out6.asd"); //utworzenie pliku ze skompresowanymi danymi
	out.writeToFile(image.getBMPinfo(), reinterpret_cast<char*>(&result[0]), result.size() * sizeof(char));//zapisanie naglowka i skompresowanej tablicy
}

void Menu::decompressPacking6()
{
	BytePacking6 depack;
	outHeader readHeader; //stworzenie obiektu do odczytu naglowka
	std::ifstream readFile;
	std::vector<Uint8> buffor; //skompresowana tab
	std::vector<Uint8> decompressbuffor; //zdekompresowana tab

	readFile.open("out6.asd", std::ios_base::binary);
	readFile.read(reinterpret_cast<char*>(&readHeader), sizeof(readHeader));
	readFile.seekg(22, std::ios_base::beg); // ustawienie sie na bajcie od ktorego zaczyna sie skompresowana tablica

	buffor.resize(readHeader.capacityForTab);
	readFile.read(reinterpret_cast<char*>(&buffor[0]), readHeader.capacityForTab);

	decompressbuffor = depack.decompression6bit(buffor);
	std::cout << std::endl << "Dekompresja zakończona sukcesem!" << std::endl;
	system("pause");

	image.saveToBMP(decompressbuffor); //zapis obrazka skompresoeanego
}

void Menu::Huffman()
{
	std::vector<SDL_Color> buffor;

	zliczaniePowtorzen(buffor);

	system("pause");
}



bool Menu::levelCompress()
{
	
	compressMenu();
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
		Huffman();
		break;
	}
	case '3':
	{
		bytePackingWelcome();
		bytePacking6();
		break;
	}
	case '4':
	{
		choice = 0;
		system("cls");
		return true;
	}
	default:
		system("cls");
		std::cout << "Zly wybor, wracam do Menu Glownego" << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
	return false;
}

bool Menu::levelDecompress()
{

	decompressMenu();
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		std::cout << "Nastepuje dekompresja, Prosze czekac..." << std::endl;
		decompressByteRun();
		system("cls");
		break;
	}
	case '2':
	{
		std::cout << "Nastepuje dekompresja, Prosze czekac..." << std::endl;
		break;
	}
	case '3':
	{
		std::cout << "Nastepuje dekompresja, Prosze czekac..." << std::endl;
		decompressPacking6();
		system("cls");
		break;
	}
	case '4':
	{
		choice = 0;
		system("cls");
		return true;
	}
	default:
		system("cls");
		std::cout << "Zly wybor, wracam do Menu Glownego" << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
	return false;
}


Menu::~Menu()
{
}
