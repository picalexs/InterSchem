#include "functiiNod.h"
#include "verificareZonaSimbol.h"
#include <vector>

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

nod* gasesteNodRecursiv(nod* nodCurent, dateNod date) {
	if (nodCurent == nullptr)
		return nullptr;
	Vector2i pozMouse;
	pozMouse.x = date.x;
	pozMouse.y = date.y;
	if (verificareSimbolInZona(pozMouse, nodCurent->date)) {
		cout << "gasit in zona:" << endl;
		return nodCurent;
	}
	nod* nodGasit = gasesteNodRecursiv(nodCurent->st, date);
	if (nodGasit != nullptr)
		return nodGasit;
	return gasesteNodRecursiv(nodCurent->dr, date);
}

nod* gasesteNodInArbore(arbore A, dateNod date) {
	if (A.radacina == nullptr)
		return nullptr;
	return gasesteNodRecursiv(A.radacina, date);
}

nod* gasesteNodCuPozMouse(RenderWindow& window, arbore &A) {
	if (A.radacina == nullptr)
		return nullptr;
	Vector2i pozitieMouse = Mouse::getPosition(window);
	dateNod nodPePozitieMouse;
	nodPePozitieMouse.x = pozitieMouse.x;
	nodPePozitieMouse.y = pozitieMouse.y;
	return gasesteNodRecursiv(A.radacina, nodPePozitieMouse);
}

nod* gasesteNodListaCuPozMouse(RenderWindow &window) {
	Vector2i pozitieMouse = Mouse::getPosition(window);
	dateNod nodPePozitieMouse;
	nodPePozitieMouse.x = pozitieMouse.x;
	nodPePozitieMouse.y = pozitieMouse.y;

	for (auto& A : listaArbori) {
		nod* nodGasit = gasesteNodInArbore(A, nodPePozitieMouse);
		if (nodGasit != nullptr) {
			return nodGasit;
		}
	}
	return nullptr;
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

int numarNoduriDinArbore(arbore A) {
	if (A.radacina == nullptr)
		return 0;
	return A.nrNoduri;
}

int numarNoduriDinListaArbori() {
	int nrNoduri = 0;
	for (auto A : listaArbori)
		nrNoduri += numarNoduriDinArbore(A);
	return nrNoduri;
}

void stergereIntregArbore(nod*& N) {
	if (N == nullptr)
		return;

	stergereIntregArbore(N->st);
	stergereIntregArbore(N->dr);

	delete N;
	N = nullptr;

}

void stergereArboreCuRadacina(arbore& A) {
	if (A.radacina == nullptr)
		return;
	stergereIntregArbore(A.radacina);
	initializareArbore(A);
}

void stergereDinListaArbori() {
	for (int i = 0; i < listaArbori.size();) {
		if (listaArbori[i].radacina == nullptr) {
			listaArbori.erase(listaArbori.begin() + i);
		}
		else {
			++i;
		}
	}
}

void stergereNodFaraSubarbore(arbore& A, nod* N) {
	if (N == nullptr)
		return;

	nod* subarbore1 = nullptr;
	nod* subarbore2 = nullptr;

	if (N->st != nullptr) {
		subarbore1 = N->st;
		N->st = nullptr;
	}
	if (N->dr != nullptr) {
		subarbore2 = N->dr;
		N->dr = nullptr;
	}

	if (subarbore1 != nullptr) {
		arbore SubarboreNou;
		atribuireArbore(SubarboreNou, subarbore1->date);
		listaArbori.insert(listaArbori.begin(), SubarboreNou);
	}

	if (subarbore2 != nullptr) {
		arbore SubarboreNou;
		atribuireArbore(SubarboreNou, subarbore2->date);
		listaArbori.insert(listaArbori.begin(), SubarboreNou);
	}
	stergereArboreCuRadacina(A);
	stergereDinListaArbori();
}
