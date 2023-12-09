#pragma once
#include "structs.h"

dateNod schimbareDate(int tip,string expresie,int x,int y);

void initializareNod(nod& N);

void atribuireNod(nod& N, dateNod date);

bool esteNodNull(nod* N);

nod* creareNodNull();

nod* creareNod(dateNod date);

void inserareFiu(nod* tata, bool fiu, dateNod date);

void initializareArbore(arbore& A);

void atribuireArbore(arbore& A, dateNod date);

bool esteArboreNull(arbore& A);

nod* gasesteNodRecursiv(nod* nodCurent, dateNod date);

nod* gasesteNodInArbore(arbore A, dateNod date);

nod* gasesteNodInListaArbori(dateNod date);

int numaraNoduri(nod* N);

int numarNoduriDinArbore(arbore A);

int numarNoduriDinListaArbori();

void stergereIntregArbore(nod*& N);

void stergereArboreCuRadacina(arbore& A);

void stergereNodFaraSubarbore(arbore& A, nod *N);