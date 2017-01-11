#include "OurFormat.h"


OurFormat::OurFormat(std::string outName)  //otwarcie pliku do zapisu
{
		
	outFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		outFile.open(outName, std::ios_base::ate | std::ios_base::binary);
	}
	catch(const std::ofstream::failure &exc)
	{
		std::cerr << "Catched exception during opening: " << exc.what();

		getchar();getchar();
		exit(-1);
	}
}

bool OurFormat::writeBin(char * buff,int size) //? po czo to .. 
{
	outFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		outFile.write(buff, size);
	}
	catch (const std::ofstream::failure &exc)
	{
		std::cerr << "Catched exception during writing to file: " << exc.what();
	}
	return true;
}

bool OurFormat::writeToFile(const SDL_Surface *info, char * buff, const int & compression, const int & size)
{
	generateHeader(info, size,compression);   //stworzenie naglowka

	writeBin(RCAST<char*>(&header), sizeof(header)); //wpisanie go do pliku

	writeBin(buff, size);

	return true;
}


outHeader OurFormat::generateHeader(const SDL_Surface *info,const int &size,const int &compression)
{
	header.compression = compression;
	header.headerSize = sizeof(header);
	header.isGreyScale = 0;
	header.height = info->h;
	header.width = info->w;
	header.capacityForTab = size;
	return header;

}

void OurFormat::closeFile()
{
	outFile.close();
}


OurFormat::~OurFormat()
{
	closeFile();
}
