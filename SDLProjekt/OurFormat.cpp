#include "OurFormat.h"


OurFormat::OurFormat(std::string outName)
{
	outFile.open(outName, std::ios_base::ate | std::ios_base::binary);
	if (!outFile.good())
	{
		std::cout << "Error during opening " << std::endl;
		exit(-1);
	}
}

void OurFormat::writeBin(char * buff,int size)
{
	outFile.write(buff, size);
}

bool OurFormat::writeToFile(const SDL_Surface *info, char * buff, const int & size)
{
	generateHeader(info, size);
	writeBin(reinterpret_cast<char*>(&header), sizeof(header));
	if (outFile.bad())
		return false;
	writeBin(buff, size);
	if (outFile.bad())
		return false;
	return true;
}

void OurFormat::readBin(const char * buff, int size)
{

}

void OurFormat::generateHeader(const SDL_Surface *info,const int &size)
{
	header.compression = 1;
	header.headerSize = sizeof(header);
	header.isGreyScale = 0;
	header.height = info->h;
	header.width = info->w;
	header.capacityForTab = size;

}

void OurFormat::closeFile()
{
	outFile.close();
}


OurFormat::~OurFormat()
{
	closeFile();
}
