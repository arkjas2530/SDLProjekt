#include "Menu.h"



Menu::Menu()
	:choice(0)
{
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}
void Menu::programMenu()
{
	std::cout << "Witaj, w programie do Kompresji i Dekompresji danych" << std::endl;
	std::cout << "1.Kompresja" << std::endl;
	std::cout << "2.Dekompresja" << std::endl;
	std::cout << "3.Zakoncz program" << std::endl;
	std::cout << "Twoj Wybor ";
}

void Menu::colorMenu()
{
	std::cout << "Jaki chcesz otrzymac obrazek :" << std::endl;
	std::cout << "1.Kolorowy" << std::endl;
	std::cout << "2.W odcieniach szarosci" << std::endl;
	std::cout << "Twoj wybor : ";
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
	std::cout << "Prosze czekac program pracuje" << std::endl;
}

void Menu::bytePackingWelcome()
{
	std::cout << "-------Upakowanie 6 bitowe-----" << std::endl;
	std::cout << "Prosze czekac program pracuje" << std::endl;
}

void Menu::huffmanWelcome()
{
	std::cout << "----------Huffman--------" << std::endl;
	std::cout << "Prosze czekac program pracuje" << std::endl;
}

void Menu::loadingImage()
{
	try
	{
		image.load(name);
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Catched error during loading image: " << e.what() << std::endl;
		e.getName();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
}

void Menu::decompressionError()
{
	size_t pos = name.find(".asd");

	try
	{
		if (pos == std::string::npos)
		{
			LoadSaveExc exc;
			exc.setName(name);
			exc.setMsg("Wrong file extension was entered. Correct file extension is asd");
			throw exc;
		}
		file.open(name, std::ios::binary);
		if (!file.good())
		{
			LoadSaveExc exc;
			exc.setName(name);
			exc.setMsg("Cannot open file! Extension was correct");
			throw exc;
		}
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Catched error: " << e.what() << std::endl;
		e.getName();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ifstream::failure &exc)
	{
		std::cerr << "Catched error while writing file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
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
			colorMenu();
			std::cin >> colorchoice;
			if (colorchoice == '1' || colorchoice == '2')
				levelCompress();
			else
			{
				std::cout << "Zly wybor" << std::endl;
				getchar();getchar();
			}
			
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

void Menu::ByteRun(char colorchoice)
{
	std::vector<SDL_Color> buffor;	//tablica zawierajaca struktury color z rgb
	std::vector<char> result;		//skompresowana tablica
	BYTERUN byterun;

	buffor = image.pixelArr();		 
	changebuffor(buffor); //utrata 2 bitow

	result = byterun.compressBT(buffor,colorchoice); // wywola sie tylko konstruktor przenoszenia przez std move


	std::cout << "Prosze podac nazwe skompresowanego pliku" << std::endl;
	std::cin >> name;
	try
	{
		OurFormat out(name); //utworzenie pliku ze skompresowanymi danymi
		out.writeToFile(image.getBMPinfo(), RCAST<char*>(&result[0]), 1, static_cast<int>(result.size() * sizeof(char)));//zapisanie naglowka i skompresowanej tablicy
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Catched error during creating format: " << e.what() << std::endl;
		e.getName();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while writing file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
}

void Menu::decompressByteRun()
{

	BYTERUN DC;
	outHeader readHeader; //stworzenie obiektu do odczytu naglowka
	
	std::vector<char> buffor; //skompresowana tab
	std::vector<SDL_Color> decompressbuffor; //zdekompresowana tab


	try
	{
		file.read(RCAST<char*>(&readHeader), sizeof(readHeader));
		file.seekg(22, std::ios_base::beg);
		if (readHeader.compression != 1)
		{
			LoadSaveExc exc;
			exc.setMsg("File wasn't compressed by BYTERUN!");
			throw exc;
		}
		buffor.resize(readHeader.capacityForTab);
		file.read(RCAST<char*>(&buffor[0]), readHeader.capacityForTab);
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Error Code: " << e.what();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while reading file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
	decompressbuffor = DC.decompressBT(buffor);

	SDL image(false, readHeader.width, readHeader.height);
	image.saveToBMP(decompressbuffor); //zapis obrazka skompresoeanego
}

void Menu::bytePacking6(char colorchoice)
{

	std::vector<SDL_Color> buffor;	//tablica zawierajaca struktury color z rgb
	std::vector<Uint8> result;		//skompresowana tablica

	image.load(name);
	buffor = image.pixelArr();
	changebuffor(buffor); //utrata 2 bitow

	BytePacking6 pack;
	result = pack.compression6bit(buffor,colorchoice);
	

	std::cout << "Prosze podac nazwe skompresowanego pliku" << std::endl;
	std::cin >> name;
	try
	{
		OurFormat out(name); //utworzenie pliku ze skompresowanymi danymi
		out.writeToFile(image.getBMPinfo(), RCAST<char*>(&result[0]), 3, static_cast<int>(result.size() * sizeof(char)));//zapisanie naglowka i skompresowanej tablicy
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Catched error during creating format: " << e.what() << std::endl;
		e.getName();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while writing file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}

}

void Menu::decompressPacking6()
{
	BytePacking6 depack;
	outHeader readHeader; //stworzenie obiektu do odczytu naglowka
	std::vector<Uint8> buffor; //skompresowana tab
	std::vector<Uint8> decompressbuffor; //zdekompresowana tab

	try
	{
		file.read(RCAST<char*>(&readHeader), sizeof(readHeader));
		if (readHeader.compression != 3)
		{
			LoadSaveExc exc;
			exc.setMsg("File wasn't compressed by 6Packing!");
			throw exc;
		}
		buffor.resize(readHeader.capacityForTab);
		file.read(RCAST<char*>(&buffor[0]), readHeader.capacityForTab);
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Error Code: " << e.what();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while reading file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
	SDL image(false, readHeader.width, readHeader.height);


	decompressbuffor = depack.decompression6bit(buffor);

	image.saveToBMP(decompressbuffor); //zapis obrazka skompresoeanego
}

void Menu::Huffman(char colorchoice)
{
	std::vector<SDL_Color> buffor;	//tablica zawierajaca struktury color z rgb
	image.load(name);
	
	buffor = image.pixelArr();
	changebuffor(buffor); //utrata 2 bitow
	HUFFMAN Huffman;

	std::cout << "Prosze podac nazwe skompresowanego pliku" << std::endl;
	std::cin >> name;
	try
	{
		OurFormat out(name); //utworzenie pliku ze skompresowanymi danymi
		size_t size = Huffman.huffmanCompress(buffor, colorchoice);
		Huffman.makeCompressedFile(out, image.getBMPinfo(), static_cast<int>(size));
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Catched error during creating format: " << e.what() << std::endl;
		e.getName();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while writing file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}
}

void Menu::decompressHuffman()
{
	HUFFMAN depack;
	outHeader readHeader; //stworzenie obiektu do odczytu naglowka

	std::vector<Uint8> buffor; //skompresowana tab
	std::vector<Uint8> decompressbuffor; //zdekompresowana tab

	try
	{
		file.read(RCAST<char*>(&readHeader), sizeof(readHeader));
		if (readHeader.compression != 2)
		{
			LoadSaveExc exc;
			exc.setMsg("File wasn't compressed by Huffman!");
			throw exc;
		}
		buffor.resize(readHeader.capacityForTab);
		SDL image(false, readHeader.width, readHeader.height);
		decompressbuffor = depack.huffmanDecompress(readHeader.capacityForTab, file);

		image.saveToBMP(decompressbuffor); //zapis obrazka skompresoeanego
	}
	catch (LoadSaveExc &e)
	{
		std::cerr << "Error Code: " << e.what();
		getchar();getchar();
		exit(-1);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched error while reading file: " << exc.what();
		getchar();getchar();
		exit(-1);
	}
	catch (...)
	{
		std::cerr << "Catched undefined error";
		getchar();getchar();
		exit(-1);
	}

}

bool Menu::levelCompress()
{
	std::cout << "Prosze podac nazwe obrazka do odczytu: " << std::endl;
	std::cin >> name;
	loadingImage();

	compressMenu();
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		ByterunWelcome();
		ByteRun(colorchoice);
		break;
	}
	case '2':
	{
		huffmanWelcome();
		Huffman(colorchoice);
		break;
	}
	case '3':
	{
		bytePackingWelcome();
		bytePacking6(colorchoice);
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
	std::cout << "Prosze podac nazwe pliku do dekompresji: " << std::endl;
	std::cin >> name;
	decompressionError();

	decompressMenu();
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		ByterunWelcome();
		decompressByteRun();
		system("cls");
		break;
	}
	case '2':
	{
		huffmanWelcome();
		decompressHuffman();
		break;
	}
	case '3':
	{
		bytePackingWelcome();
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

void Menu::changebuffor(std::vector<SDL_Color> &buffor)
{
	int buffsize= static_cast<int>(buffor.size());
	int i = 0;
	while (i < buffsize)
	{
		buffor[i].r &= 0xFC;
		buffor[i].g &= 0xFC;
		buffor[i].b &= 0xFC;
		i++;
	}
}

Menu::~Menu()
{
}
