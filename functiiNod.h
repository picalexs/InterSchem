#pragma once
#include "structs.h"
#include <string>
#include <iostream>

using namespace std;

void initNod(nod &N) {
	N.tip.clear();
	N.expresie.clear();
	N.x = 0; N.y = 0;
	N.st = NULL; N.dr = NULL;
}

bool esteNodNull(nod &N) {
	return N.tip.empty();
}

nod *creareNod() {
	nod *N=new nod;
	initNod(*N);
	return N;
}

void initArbore(arbore &A, string expresieNoua) {
	nod *nodNou = creareNod();
	A.radacina->expresie = expresieNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(arbore& A) {
	return (A.radacina == NULL);
}

arbore* creareArbore() {
	arbore* A = new arbore;
	initArbore(*A);
}
