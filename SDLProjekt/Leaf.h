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
	Leaf();
	Leaf(unsigned char _wartosc,unsigned int _iloscPowtorzen);
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

struct Numrep
{
	bool operator ()( Leaf & leaf1,  Leaf & leaf2)
	{
		
		if (leaf1.pobierzIloscPowtorzen() < leaf2.pobierzIloscPowtorzen()) return true;

		if (leaf1.pobierzIloscPowtorzen() > leaf2.pobierzIloscPowtorzen()) return false;

		return false;
	}
};

#endif LEAF_H_