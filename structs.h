#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct dateNod {
	int tip = -1; //0-START, 1-STOP, 2-Atribuire, 3-Citire, 4-Afisare, 5-Daca/While
	string expresie;
	int x = 0, y = 0;
	int lng;
};

struct nod {
	dateNod date;
	nod* st = nullptr, * dr = nullptr;
};

struct arbore {
	nod* radacina = nullptr;
	int nrNoduri = 0;
};

extern vector<string> numeNoduri;
extern vector<arbore> listaArbori;
extern vector<pair<dateNod, dateNod>> listaLinii;
extern vector<dateNod> expresii;
extern unordered_map<string,long double> variabile;