#include "Byterun.h"

BYTERUN::BYTERUN()
	:n1(0),n2(0),i(0)
{}

bool operator==(const SDL_Color &_typ1, const SDL_Color &_typ2)
{
	if (_typ1.r == _typ2.r && _typ1.g == _typ2.g && _typ1.b == _typ2.b)
		return true;
	else
		return false;
}

void BYTERUN::compressBT (std::vector<SDL_Color> tab)
{
	/*
	using lol = std::pair<int, double>;
	std::pair<int, double> foo = { 1, 1.3 };
	std::vector<lol> hehe;
	zamiast tab result
	*/
	
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
			result.push_back(tab[i].r);
			result.push_back(tab[i].g);
			result.push_back(tab[i].b);
			i++;
		}
		else
		{
			n2 = result.size(); //pozycja liczby okreslajacej ilosc niepowtarzajacych sie liczb
			result.push_back(0); //wpisanie na pozycje n , po obczajeniu liczb zastapi sie ja

			while (i < tab.size() - 1 && n1 < 127)
				if (tab[i].r != tab[i + 1].r || tab[i].g != tab[i + 1].g || tab[i].b != tab[i + 1].b)
				{
					result.push_back(tab[i].r);
					result.push_back(tab[i].g);
					result.push_back(tab[i].b);
					n1++;
					i++;				
				}
				else
					break;
			
			if  (i == tab.size()-1)
			{
				result.push_back(tab[i].r);
				result.push_back(tab[i].g);
				result.push_back(tab[i].b);
				n1++;
				i++;
			
			}

			result[n2] = n1 - 1;
			i++;
		}	

	}


}

