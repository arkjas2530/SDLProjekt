#pragma once
#include<vector>
#include "OurFormat.h"
#include<SDL.h>
#include<iostream>
#include<string>
#include<cstdlib>

class Leaf;

// void wypelnijSterte(unsigned char * tab); 
// Leaf * algorytmHuffmana(Sterta<Lisc> & a);

void wypiszWynik(Leaf* korzen, std::string kod); // drukuje na ekran optymalne binarne kody prefiksowe
void zwolnijPamiec(Leaf* korzen); // zwalnia pamiec (drzewo)
void zliczaniePowtorzen(std::vector<SDL_Color>& buffor);







