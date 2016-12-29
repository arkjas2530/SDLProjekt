#ifndef LEAF_H_
#define LEAF_H_

class Leaf
{
protected:
	Leaf * leweDziecko;
	Leaf * praweDziecko;
	unsigned char wartosc;
	unsigned int iloscPowtorzen;

public:
	Leaf(unsigned char _wartosc = '\0',unsigned int _iloscPowtorzen = 0);
	void ustawLeweDziecko(Leaf * l);
	void ustawPraweDziecko(Leaf * l);
	void ustawIloscPowtorzen(unsigned int I);
	void ustawWartosc(unsigned char w);
	unsigned int pobierzIloscPowtorzen();
	unsigned char pobierzWartosc();
	Leaf* pobierzLeweDziecko();
	Leaf* pobierzPraweDziecko();
	bool operator>(Leaf & l);
	bool operator<(Leaf & l);
	bool operator>=(Leaf & l);
	bool operator<=(Leaf & l);
};

struct OperatorQueue
{
	bool operator ()(Leaf & leaf1, Leaf & leaf2)
	{

		if (leaf1.pobierzIloscPowtorzen() > leaf2.pobierzIloscPowtorzen()) return true;

		else  return false;

	}
};

#endif LEAF_H_