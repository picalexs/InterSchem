#include "functiiNod.h"

dateNod schimbareDate(int tip, string expresie, int x, int y) {
	dateNod date;
	date.tip = tip;
	date.expresie = expresie;
	date.x = x;
	date.y = y;
	return date;
}

void initializareNod(nod& N) {
	N.date.tip = -1;
	N.date.expresie.clear();
	N.date.x = 0; N.date.y = 0;
	N.st = nullptr; N.dr = nullptr;
}

void atribuireNod(nod& N, dateNod date) {
	N.date.tip = date.tip;
	N.date.expresie = date.expresie;
	N.date.x = date.x; N.date.y = date.y;
	N.st = nullptr; N.dr = nullptr;
}

bool esteNodNull(nod* N) {
	return (N == nullptr);
}

nod* creareNodNull() {
	nod* N = new nod;
	initializareNod(*N);
	return N;
}

nod* creareNod(dateNod date) {
	nod* N = new nod;
	atribuireNod(*N, date);
	return N;
}

void inserareFiu(nod* tata, bool fiu, dateNod date) {
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

void initializareArbore(arbore& A) {
	A.radacina = nullptr;
	A.nrNoduri = 0;
}

void atribuireArbore(arbore& A, dateNod date) {
	nod* radacinaNoua = creareNod(date);
	A.radacina = radacinaNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(arbore& A) {
	return (A.radacina == nullptr);
}

arbore* creareArbore(dateNod date) {
	arbore* A = new arbore;
	if (A == nullptr) {
		throw("EROARE");
	}
	atribuireArbore(*A, date);
	return A;
}

nod* gasesteNodRecursiv(nod* nodCurent, dateNod date) {
	if (nodCurent == nullptr)
		return nullptr;

	if (nodCurent->date.x == date.x && nodCurent->date.y == date.y)
		return nodCurent;

	nod* nodGasit = gasesteNodRecursiv(nodCurent->st, date);
	if (nodGasit != nullptr)
		return nodGasit;

	return gasesteNodRecursiv(nodCurent->dr, date);
}

nod* gasesteNodInArbore(arbore* A, dateNod date) {
	if (A == nullptr || A->radacina == nullptr)
		return nullptr;

	return gasesteNodRecursiv(A->radacina, date);
}

nod* gasesteNodInListaArbori(dateNod date) {
	for (size_t i = 0; i < listaArbori.size(); ++i) {
		nod* nodGasit = gasesteNodInArbore(listaArbori[i], date);
		if (nodGasit != nullptr)
			return nodGasit;
	}
	return nullptr;
}


int numaraNoduri(nod* N) {
	if (N == nullptr)
		return 0;
	return 1 + numaraNoduri(N->st) + numaraNoduri(N->dr);
}

void stergereIntregArbore(nod*& N) {
	if (N == nullptr)
		return;

	stergereIntregArbore(N->st);
	stergereIntregArbore(N->dr);

	delete N;
	N = nullptr;
}

void stergereArboreCuRadacina(arbore*& A) {
	if (A == nullptr)
		return;
	stergereIntregArbore(A->radacina);
	delete A;
	A = nullptr;
}


void stergereNodFaraSubarbore(arbore*& A, nod* N) {
	if (N == nullptr)
		return;

	nod* subarbore1 = nullptr;
	nod* subarbore2 = nullptr;

	if (N->st != nullptr) {
		subarbore1 = N->st;
		N->st = nullptr;
	}
	else if (N->dr != nullptr) {
		subarbore2 = N->dr;
		N->dr = nullptr;
	}

	if (subarbore1 != nullptr) {
		arbore* SubarboreNou = creareArbore(subarbore1->date);
		listaArbori.push_back(SubarboreNou);
		stergereIntregArbore(subarbore1);
	}

	if (subarbore2 != nullptr) {
		arbore* SubarboreNou = creareArbore(subarbore2->date);
		listaArbori.push_back(SubarboreNou);
		stergereIntregArbore(subarbore2);
	}
	stergereArboreCuRadacina(A);
}