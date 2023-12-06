#pragma once
#include "structs.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void initializareNod(nod &N) {
	N.date.tip = 0;
	N.date.expresie.clear();
	N.date.x = 0; N.date.y = 0;
	N.st = NULL; N.dr = NULL;
}

void atribuireNod(nod& N, dateNod date) {
	N.date.tip = date.tip;
	N.date.expresie= date.expresie;
	N.date.x = date.x; N.date.y = date.y;
	N.st = NULL; N.dr = NULL;
}

bool esteNodNull(nod *N) {
	return (N == nullptr);
}

nod* creareNodNull() {
	nod* N = new nod;
	initializareNod(*N);
	return N;
}

nod* creareNod(dateNod date) {
	nod* N = creareNodNull();
	atribuireNod(*N, date);
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
	return (N.date.tip == 'I');
}

void inserareNod(nod* tata, bool fiu, dateNod date) {
	if (esteNodNull(tata))
		return;
	nod* N = creareNod(date);
	if (fiu == 0) {//bool fiu: 0-fiu st., 1-fiu dr.
		tata->st = N;
	}
	else {
		tata->dr = N;
	}
}

void atribuireArbore(arbore &A, dateNod date) {
	nod *radacinaNoua = creareNod(date);
	A.radacina = radacinaNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(arbore& A) {
	return (A.radacina == nullptr);
}

arbore* creareArbore(dateNod date) {
	arbore* A = new arbore;
	if (A == nullptr) {
		throw("EROARE", A);
	}
	atribuireArbore(*A, date);
	return A;
}
