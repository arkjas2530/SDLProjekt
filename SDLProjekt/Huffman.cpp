#include"Huffman.h"
#include"Leaf.h"




/*
void wypelnijSterte(unsigned char * tab)
{
unsigned char liczba;
int ilosc;

for (int i = 0; i<256; i++)
{
liczba = i;
ilosc = tab[i];

Leaf leaf(liczba, ilosc);

-> -> TUTAJ MA BYC DODANIE ELEMENTU DO KOPCA    ""s.wstaw(leaf);""  <- <-
}
}

Leaf * algorytmHuffmana(Sterta<Leaf> & a)
{
Leaf* ostatni_lewy = nullptr; // pamieta adres ostatnio dodanych dzieci
Leaf* ostatni_prawy = nullptr;

while (a.pobierzliczbaElementow())
{
Leaf* chwilowy1 = new Leaf(); // miejsce na nowe dzieci i nowy korzen
Leaf* chwilowy2 = new Leaf();
Leaf* n_korzen = new Leaf();

if (a.pobierzliczbaElementow() == 1) // sciaga ostatni element w kolejce, konczy algorytm, zwraca korzen drzewa
{
*n_korzen = a.pobierzElement();
n_korzen->ustawLeweDziecko(ostatni_lewy);
n_korzen->ustawPraweDziecko(ostatni_prawy);
n_korzen->ustawIloscPowtorzen(ostatni_lewy->pobierzIloscPowtorzen() + ostatni_prawy->pobierzIloscPowtorzen());
n_korzen->ustawWartosc(ostatni_lewy->pobierzWartosc() + ostatni_prawy->pobierzWartosc());
return n_korzen;
}
else // tworzy nowy korzen, dolacza do niego dzieci, wstawia nowy korzen do kolejki
{
*chwilowy1 = a.pobierzElement();
*chwilowy2 = a.pobierzElement();

n_korzen->ustawLeweDziecko(chwilowy1);
n_korzen->ustawPraweDziecko(chwilowy2);
n_korzen->ustawIloscPowtorzen(chwilowy1->pobierzIloscPowtorzen() + chwilowy2->pobierzIloscPowtorzen());
n_korzen->ustawWartosc(chwilowy1->pobierzWartosc() + chwilowy2->pobierzWartosc());

ostatni_lewy = chwilowy1;
ostatni_prawy = chwilowy2;

a.wstaw(*n_korzen);
}
}

}
*/

void wypiszWynik(Leaf* korzen, std::string kod) // drukuje na ekran optymalne binarne kody prefiksowe
{
	if (!korzen->pobierzLeweDziecko())
		std::cout << korzen->pobierzIloscPowtorzen() << " " << kod << std::endl;
	else
	{
		wypiszWynik(korzen->pobierzLeweDziecko(), kod + "0");
		wypiszWynik(korzen->pobierzPraweDziecko(), kod + "1");
	}
}

void zwolnijPamiec(Leaf * korzen) // zwalnia pamiec (drzewo)
{
	if (korzen->pobierzLeweDziecko())
		zwolnijPamiec(korzen->pobierzLeweDziecko());
	if (korzen->pobierzPraweDziecko())
		zwolnijPamiec(korzen->pobierzPraweDziecko());
	delete korzen;
}

void zliczaniePowtorzen(std::vector<SDL_Color>& buffor)
{
	unsigned char tab[256];

	for (int i = 0; i <= 255; i++)
	{
		tab[i] = 0;
	}

	/*
	for (int i = 0; i <= 32; i++)
	{

	tab[buffor[i].r]++;
	tab[buffor[i].g]++;
	tab[buffor[i].b]++;
	}
	*/

	for (int i = 0; i < 256; i++)
	{
		std::cout << "Ilosc wystapien " << i << " :" << tab[i] << std::endl;

	}

}


