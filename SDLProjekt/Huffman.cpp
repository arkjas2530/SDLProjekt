#include"Huffman.h"

/*
void wypelnijSterte(unsigned char * powtorzenia)
{
unsigned char liczba;
int ilosc;

for (int i = 0; i<256; i++)
{
liczba = i;
ilosc = powtorzenia[i];

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

HUFFMAN::HUFFMAN()
{
	powtorzenia.resize(256);
	heap.reserve(256);
}

void HUFFMAN::wypiszWynik(Leaf * korzen, std::string kod)
{
	if (!korzen->pobierzLeweDziecko())
		std::cout << int(korzen->pobierzWartosc()) << " " << kod << std::endl;
	else
	{
		wypiszWynik(korzen->pobierzLeweDziecko(), kod + "0");
		wypiszWynik(korzen->pobierzPraweDziecko(), kod + "1");
	}
}

void HUFFMAN::zwolnijPamiec(Leaf * korzen)// zwalnia pamiec (drzewo)
{
	if (korzen->pobierzLeweDziecko())
		zwolnijPamiec(korzen->pobierzLeweDziecko());
	if (korzen->pobierzPraweDziecko())
		zwolnijPamiec(korzen->pobierzPraweDziecko());
	delete korzen;
}

void HUFFMAN::zliczaniePowtorzen(std::vector<SDL_Color>& buffor)
{
	size_t buff_size=buffor.size();
	for (unsigned int i = 0; i < buff_size; ++i)
	{
		++powtorzenia[buffor[i].r];
		++powtorzenia[buffor[i].g];
		++powtorzenia[buffor[i].b];
	}

	for (int i = 0; i < 256; i++)
	{
		std::cout << "Ilosc wystapien " << i << " :" << powtorzenia[i] << std::endl;
	}
}

Leaf HUFFMAN::pobierzElement()
{
	
	Leaf element = kolejkaPriorytetowa.top();
	kolejkaPriorytetowa.pop();

	return element;
}

void HUFFMAN::wstaw(const Leaf &x)
{
	kolejkaPriorytetowa.push(x);
}

void HUFFMAN::wypelnijSterte()
{
	//std::vector<Leaf> heap;
	unsigned char liczba;	// kolor
	unsigned int ilosc;		// powtorzenie koloru

	for (int i = 0; i < 256; i++)
	{
		liczba = i;
		ilosc = powtorzenia[i];

		Leaf leaf(liczba, ilosc);

		kolejkaPriorytetowa.push(leaf);
	}
}

Leaf * HUFFMAN::algorytmHuffmana()
{
	Leaf* ostatni_lewy = nullptr; // pamieta adres ostatnio dodanych dzieci
	Leaf* ostatni_prawy = nullptr;

	while (!kolejkaPriorytetowa.empty())
	{
		Leaf* chwilowy1 = new Leaf(); // miejsce na nowe dzieci i nowy korzen
		Leaf* chwilowy2 = new Leaf();
		Leaf* n_korzen = new Leaf();

		if (kolejkaPriorytetowa.size() == 1) // sciaga ostatni element w kolejce, konczy algorytm, zwraca korzen drzewa
		{
			*n_korzen = pobierzElement();
			n_korzen->ustawLeweDziecko(ostatni_lewy);
			n_korzen->ustawPraweDziecko(ostatni_prawy);
			n_korzen->ustawIloscPowtorzen(ostatni_lewy->pobierzIloscPowtorzen() + ostatni_prawy->pobierzIloscPowtorzen());
			n_korzen->ustawWartosc(0);
			return n_korzen;
		}
		else // tworzy nowy korzen, dolacza do niego dzieci, wstawia nowy korzen do kolejki
		{
			*chwilowy1 = pobierzElement();
			*chwilowy2 = pobierzElement();

			n_korzen->ustawLeweDziecko(chwilowy1);
			n_korzen->ustawPraweDziecko(chwilowy2);
			n_korzen->ustawIloscPowtorzen(chwilowy1->pobierzIloscPowtorzen() + chwilowy2->pobierzIloscPowtorzen());
			n_korzen->ustawWartosc(0);

			ostatni_lewy = chwilowy1;
			ostatni_prawy = chwilowy2;

			wstaw(*n_korzen);
		}
	}

}
HUFFMAN::~HUFFMAN()
{
}
