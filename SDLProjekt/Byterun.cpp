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

int BYTERUN::compressBT (std::vector<SDL_Color> &tab,OurFormat &file)
{
	unsigned int i = 0;
	char n1 = 0;
	unsigned char n2 = 0;
	int counter = 0;

	char tmp = 0;

	while (i < tab.size() - 1)
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
			counter += 4;
			tmp = -n1;

			file.writeBin(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			file.writeBin(reinterpret_cast<char*>(&(tab[i])), sizeof(tab[i]));

			i++;
		}
		else
		{
			n2 = counter;
			char tmpTab[381] = {}; int j = 0;

			while (i < tab.size() - 1 && n1 < 127)
				if (tab[i].r != tab[i + 1].r || tab[i].g != tab[i + 1].g || tab[i].b != tab[i + 1].b)
				{				
					tmpTab[j++] = tab[i].r;
					tmpTab[j++] = tab[i].g;
					tmpTab[j++] = tab[i].b;
					
					counter += 3;
					n1++;
					i++;
				}
				else
					break;
			if (i == tab.size() - 1)
			{				
				counter += 3;
			
				tmpTab[j] = tab[i].r;
				tmpTab[++j] = tab[i].g;
				tmpTab[++j] = tab[i].b;
				++j;

				n1++;
				i++;

			}
			tmp = n1 - 1;
			
			file.writeBin(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			file.writeBin(reinterpret_cast<char*>(&tmpTab), j);

			counter++;
			i++;

		}

	}

	return counter;
}

