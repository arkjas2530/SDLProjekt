#include"Huffman.h"

HUFFMAN::HUFFMAN()
{
	powtorzenia.resize(256);
}

void HUFFMAN::wypiszWynik(Leaf * korzen, std::vector<bool> kod)
{
	if (!korzen->pobierzLeweDziecko())
	{
		codeMap[korzen->pobierzWartosc()] = kod;
	}
	else
	{
		kod.push_back(0);
		wypiszWynik(korzen->pobierzLeweDziecko(), kod);
		kod.push_back(1);
		wypiszWynik(korzen->pobierzPraweDziecko(), kod);
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

void HUFFMAN::huffmanCompress(const std::vector<SDL_Color>& buffor,OurFormat &out)
{
	size_t sizeBuff = buffor.size();
	size_t i = 0;
	while (i < sizeBuff)
	{
		;
	}
	std::cout << "Pause";
}

void HUFFMAN::wypelnijSterte()
{
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
