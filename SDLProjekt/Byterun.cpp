#include "Byterun.h"

BYTERUN::BYTERUN()
{}

bool operator==(const SDL_Color &_typ1, const SDL_Color &_typ2)
{
	if (_typ1.r == _typ2.r && _typ1.g == _typ2.g && _typ1.b == _typ2.b)
		return true;
	else
		return false;
}

std::vector<char> BYTERUN::compressBT(const std::vector<SDL_Color> &tab)
{
	/*
	using lol = std::pair<int, double>;
	std::pair<int, double> foo = { 1, 1.3 };
	std::vector<lol> hehe;
	zamiast tab result
	*/
	

	std::vector<char> result;
	size_t tab_size = tab.size();
	result.reserve(3*tab_size);
	
	unsigned int i = 0;
	char n1 = 0;
	size_t n2 = 0;
	
	while (i < tab_size -1)
	{
		n1 = 0;
		n2 = 0;
		if (tab[i] == tab[i + 1]) // jesli co najmniej 2 bajty sa takie same to obczaj ich dlugosc
		{
			n1++;
			i++;
			while (i < tab_size - 1 && n1 < 127 && tab[i] == tab[i + 1])
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

			while (i < tab_size - 1 && n1 < 127)
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

			if (i == tab_size - 1)
			{
				result.push_back(tab[i].r);
				result.push_back(tab[i].g);
				result.push_back(tab[i].b);
				n1++;
				i++;

			}

			result[n2] = n1 - 1;
			
		}

	}

	return std::move(result);
}
std::vector<SDL_Color> BYTERUN::decompressBT(const std::vector<char> &buffor)
{
	std::vector<SDL_Color> result;
	SDL_Color temp;
	result.resize(258132); //jak rozkminic rozmiar. . 

	int n;
	unsigned int i = 0;
	int j = 0;

	size_t buf_size = buffor.size();
	while ( i < buf_size)
	{
		n =buffor[i];
		if (n < 0)//gdy liczby sie powtarzaja
		{

			for (int z = 0; z < -n + 1; ++z,++j)
			{
				
				result[j].r=((unsigned char)buffor[i + 1]);
				result[j].g = (unsigned char)buffor[i + 2];
				result[j].b = (unsigned char)buffor[i + 3];
				//result.push_back(temp);
			}
			i += 4;
		}
		else
		{
			for (int x = 0; x < n + 1; ++x,++j)
			{

				result[j].r = ((unsigned char)buffor[i + 1]);
				result[j].g = (unsigned char)buffor[i + 2];
				result[j].b = (unsigned char)buffor[i + 3];
				i += 3;
			}
			i++;

		}

	}

	return std::move(result);
}
