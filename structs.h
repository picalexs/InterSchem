#pragma once
#include <string>
#include <iostream>

struct DateNod {
	int tip = -1; //0-START, 1-STOP, 2-Atribuire, 3-Citire, 4-Afisare, 5-Daca/While
	std::string expresie;
	float x = 0, y = 0;
};

struct Nod {
	DateNod date;
	Nod* st = nullptr, * dr = nullptr;
};

struct Arbore {
	Nod* radacina = nullptr;
	int nrNoduri = 0;
};

