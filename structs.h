#pragma once
#include <string>
#include <iostream>
using namespace std;

struct nod
{
	string expresie;
	char tip;//0-START, 1-STOP, V-Atribuire Variabila, I-If, C-Citire, A-Afisare
	int x = 0, y = 0;
	nod* st = NULL, * dr = NULL;
};

struct arbore {
	nod* radacina;
	int nrNoduri=0;
};

