#include "OurFormat.h"


OurFormat::OurFormat(std::string outName)  //otwarcie pliku do zapisu
{
	size_t pos = outName.find(".asd");
	if (pos == std::string::npos)
	{
		LoadSaveExc exc;
		exc.setName(outName);
		exc.setMsg("Wrong file extension was entered. Correct file extension is asd");
		throw exc;
	}
	outFile.open(outName, std::ios_base::ate | std::ios_base::binary);
	if (!outFile.good())
	{
		LoadSaveExc exc;
		exc.setName(outName);
		exc.setMsg("Cannot open file! Extension was correct");
		throw exc;
	}
		
}

bool OurFormat::writeBin(char * buff,int size)
{
	outFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	
	outFile.write(buff, size);
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
