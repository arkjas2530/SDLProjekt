#ifndef LEAF_H_
#define LEAF_H_

class Leaf
{
	Leaf * leweDziecko;
	Leaf * praweDziecko;
	unsigned char wartosc;
	int iloscPowtorzen;

public:
	Leaf(unsigned char _wartosc, int _iloscPowtorzen);
	void ustawLeweDziecko(Leaf * l);
	void ustawPraweDziecko(Leaf * l);
	void ustawIloscPowtorzen(int I);
	void ustawWartosc(unsigned char w);
	int pobierzIloscPowtorzen();
	unsigned char pobierzWartosc();
	Leaf* pobierzLeweDziecko();
	Leaf* pobierzPraweDziecko();
	bool operator>(Leaf & l);
	bool operator<(Leaf & l);
	bool operator>=(Leaf & l);
	bool operator<=(Leaf & l);
};

#endif LEAF_H_