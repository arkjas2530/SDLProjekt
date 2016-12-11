#include "Byterun.h"

BYTERUN::BYTERUN():n1(0),n2(0),i(0)
{
}

std::vector<int> BYTERUN::compressBT (std::vector<int> tab,std::ofstream &file)
{
	std::vector<int> result;

	while (i < tab.size()-1)
	{
		n1 = 0;
		n2 = 0;
		if (tab[i] == tab[i + 1]) // jesli co najmniej 2 bajty sa takie same to obczaj ich dlugosc
		{
			n1++;
			i++;
			while (i < tab.size() - 1 && n1 < 127 && tab[i] == tab[i + 1])
			{
				n1++;
				i++;
			}
			result.push_back(-n1);
			result.push_back(tab[i]);
			i++;
		}
		else
		{
			n2 = result.size(); //pozycja liczby okreslajacej ilosc niepowtarzajacych sie liczb
			result.push_back(0); //wpisanie na pozycje n , po obczajeniu liczb zastapi sie ja

			while (tab[i] != tab[i + 1] && i < tab.size()-1 && n1 < 127)
			{
				result.push_back(tab[i]);
				n1++;
				i++;
			}

			if (i == tab.size()-1)
			{
				result.push_back(tab[i]);
				n1++;
				i++;
			}
			result[n2] = n1 - 1;
		}	
	}
	return result;
}

