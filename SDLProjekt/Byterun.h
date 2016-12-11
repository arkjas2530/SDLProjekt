#pragma
#include<vector>
#include<fstream>

class BYTERUN
{
	int n1;
	int n2;
	int i;
	
public:
	BYTERUN();
	std::vector<int> compressBT(std::vector<int> tab,std::ofstream &file);

};
