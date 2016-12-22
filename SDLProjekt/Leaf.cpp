#include"Leaf.h"


Leaf::Leaf(unsigned char _wartosc, int _iloscPowtorzen) : wartosc(_wartosc), iloscPowtorzen(_iloscPowtorzen), leweDziecko(nullptr), praweDziecko(nullptr)
{
}

void Leaf::ustawLeweDziecko(Leaf * l)
{
	leweDziecko = l;
}

void Leaf::ustawPraweDziecko(Leaf * l)
{
	praweDziecko = l;
}

void Leaf::ustawIloscPowtorzen(int I)
{
	iloscPowtorzen = I;
}

void Leaf::ustawWartosc(unsigned char w)
{
	wartosc = w;
}

int Leaf::pobierzIloscPowtorzen()
{
	return iloscPowtorzen;
}

unsigned char Leaf::pobierzWartosc()
{
	return wartosc;
}

Leaf * Leaf::pobierzLeweDziecko()
{
	return leweDziecko;
}

Leaf * Leaf::pobierzPraweDziecko()
{
	return praweDziecko;
}

bool Leaf::operator>(Leaf & l)
{
	if (this->pobierzWartosc() > l.pobierzWartosc())
		return true;
	else
		return false;
}

bool Leaf::operator<(Leaf & l)
{
	return l.operator>(*this);
}

bool Leaf::operator>=(Leaf & l)
{
	if (this->pobierzWartosc() >= l.pobierzWartosc())
		return true;
	else
		return false;
}

bool Leaf::operator<=(Leaf & l)
{
	return l.operator>=(*this);
}


