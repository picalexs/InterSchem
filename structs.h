#pragma once
#include <string>
#include <iostream>

struct dateNod {
	int tip = -1; //0-START, 1-STOP, 2-Atribuire, 3-Citire, 4-Afisare, 5-Daca/While
	std::string expresie;
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
