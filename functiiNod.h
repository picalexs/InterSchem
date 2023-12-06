#pragma once
#include "structs.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void initNod(nod &N) {
	N.expresie.clear();
	N.tip = 0;
	N.x = 0; N.y = 0;
	N.st = NULL; N.dr = NULL;
}

nod* creareNod() {
	nod* N = new nod;
	initNod(*N);
	return N;
}

void stergereNod(nod* N) {
	if (N == nullptr)
		return;
	stergereNod(N->st);
	stergereNod(N->dr);

	N = nullptr;
	delete N;
}

bool esteVerificare(nod& N) {
	return (N.tip==0)
}

void inserareNod(nod &tata, bool fiu) {
	nod* N = creareNod();
	if (!fiu) {//bool fiu: 0-fiu st., 1-fiu dr.

	}
}

void initArbore(arbore &A, string expresieNoua) {
	nod *radacinaNoua = creareNod();
	A.radacina = radacinaNoua;
	A.radacina->expresie = expresieNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(arbore& A) {
	return (A.radacina == NULL);
}

arbore* creareArbore(string expresieNoua) {
	arbore* A = new arbore;
	if(A==nullptr)
		return;
	initArbore(*A,expresieNoua);
	return A;
}
