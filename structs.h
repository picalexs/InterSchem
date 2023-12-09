#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct dateNod {
	int tip = -1; //0-START, 1-STOP, 2-Atribuire, 3-Citire, 4-Afisare, 5-Daca/While
	string expresie;
	int x = 0, y = 0;
};

struct nod {
	dateNod date;
	nod* st = NULL, * dr = NULL;
};

struct arbore {
	nod* radacina = NULL;
	int nrNoduri = 0;
};

extern vector<string> numeNoduri;
extern vector<arbore> listaArbori;