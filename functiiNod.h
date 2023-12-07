#pragma once
#include "structs.h"

dateNod schimbareDate(int tip,string expresie,int x,int y);

void initializareNod(nod& N);

void atribuireNod(nod& N, dateNod date);

bool esteNodNull(nod* N);

nod* creareNodNull();

nod* creareNod(dateNod date);

void stergereNod(nod* N);

void inserareFiu(nod* tata, bool fiu, dateNod date);

void initializareArbore(arbore& A);

void atribuireArbore(arbore& A, dateNod date);

bool esteArboreNull(arbore& A);

arbore* creareArbore(dateNod date);