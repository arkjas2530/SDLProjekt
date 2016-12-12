#include "OurFormat.h"


OurFormat::OurFormat(std::string outName)
{
	outFile.open(outName, std::ios_base::trunc | std::ios_base::binary);
	if (!outFile.good())
	{
		std::cout << "Error during opening " << std::endl;
		exit(-1);
	}
}

void OurFormat::writeBin(const char * buff,int size)
{
	outFile.write(buff, size);
}


OurFormat::~OurFormat()
{
	outFile.close();
}
