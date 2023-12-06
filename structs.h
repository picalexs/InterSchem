#pragma once
#include <string>
#include <iostream>
using namespace std;
vector<string> numeNoduri = {"Start", "Stop", "Atribuire", "Citire", "Afisare", "If"};
struct dateNod{
	int tip=0;//0-START, 1-STOP, 2-Atribuire Variabila, 3-Citire, 4-Afisare, 5-If
	string expresie;
	int x = 0, y = 0;
};

struct nod
{
	dateNod date;
	nod* st = NULL, * dr = NULL;
};

struct arbore {
	nod* radacina=NULL;
	int nrNoduri=0;
};

