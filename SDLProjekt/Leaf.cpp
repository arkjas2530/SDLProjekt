#include"Leaf.h"


Leaf::Leaf(unsigned char _wartosc, unsigned int _iloscPowtorzen) : wartosc(_wartosc), iloscPowtorzen(_iloscPowtorzen), leweDziecko(nullptr), praweDziecko(nullptr)
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

void Leaf::ustawIloscPowtorzen(unsigned int I)
{
	iloscPowtorzen = I;
}

void Leaf::ustawWartosc(unsigned char w)
{
	wartosc = w;
}

unsigned int Leaf::pobierzIloscPowtorzen()
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
	if (this->pobierzIloscPowtorzen() < l.pobierzIloscPowtorzen())
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
	if (this->pobierzIloscPowtorzen() >= l.pobierzIloscPowtorzen())
		return true;
	else
		return false;
}

bool Leaf::operator<=(Leaf & l)
{
	return l.operator>=(*this);
}