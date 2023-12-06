#pragma once
#include <string>
#include <iostream>

using namespace std;

struct punctLegatura {
	int x, y;
};

struct nod
{
	string tip;
	string expresie;
	int x = 0, y = 0;
	nod* st = NULL, * dr = NULL;
};

struct arbore {
	nod* radacina;
	int nrNoduri=0;
};

