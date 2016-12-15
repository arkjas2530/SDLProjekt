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

void OurFormat::readBin(const char * buff, int size)
{

}

void OurFormat::closeFile()
{
	outFile.close();
}


OurFormat::~OurFormat()
{
	outFile.close();
}
