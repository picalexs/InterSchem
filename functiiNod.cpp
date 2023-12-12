#include "functiiNod.h"
#include "verificareZonaSimbol.h"
#include <vector>

dateNod schimbareDate(const int tip, const string& expresie, const int x, const int y) {
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

void atribuireNod(nod& N, const dateNod& date) {
	N.date.tip = date.tip;
	N.date.expresie = date.expresie;
	N.date.x = date.x; N.date.y = date.y;
	N.st = nullptr; N.dr = nullptr;
}

bool esteNodNull(const nod* N) {
	return (N == nullptr);
}

nod* creareNodNull() {
	nod* N = new nod;
	initializareNod(*N);
	return N;
}

nod* creareNod(const dateNod& date) {
	nod* N = new nod;
	atribuireNod(*N, date);
	return N;
}

void inserareFiu(nod* tata, const bool fiu, const dateNod& date) {
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

void atribuireArbore(arbore& A, const dateNod& date) {
	nod* radacinaNoua = creareNod(date);
	A.radacina = radacinaNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(const arbore& A) {
	return (A.radacina == nullptr);
}

bool esteNodInArbore(nod* nodCautat, const nod* radacina) {
	if (radacina == nullptr)
		return false;
	if (radacina == nodCautat)
		return true;
	return (esteNodInArbore(nodCautat, radacina->st) || esteNodInArbore(nodCautat, radacina->dr));
}

nod* gasesteNodRecursiv(nod* nodCurent, const dateNod& date) {
	if (nodCurent == nullptr)
		return nullptr;
	Vector2i pozMouse;
	pozMouse.x = date.x;
	pozMouse.y = date.y;
	if (verificareSimbolInZona(pozMouse, nodCurent->date))
		return nodCurent;
	
	nod* nodGasit = gasesteNodRecursiv(nodCurent->st, date);
	if (nodGasit != nullptr)
		return nodGasit;
	return gasesteNodRecursiv(nodCurent->dr, date);
}

nod* gasesteNodInArbore(arbore A, const dateNod& date) {
	if (A.radacina == nullptr)
		return nullptr;
	return gasesteNodRecursiv(A.radacina, date);
}

nod* gasesteNodCuPozMouse(const RenderWindow& window, arbore &A) {
	if (A.radacina == nullptr)
		return nullptr;
	Vector2i pozitieMouse = Mouse::getPosition(window);
	dateNod nodPePozitieMouse;
	nodPePozitieMouse.x = pozitieMouse.x;
	nodPePozitieMouse.y = pozitieMouse.y;
	return gasesteNodRecursiv(A.radacina, nodPePozitieMouse);
}

nod* gasesteNodListaCuPozMouse(const RenderWindow& window)
{
	Vector2i pozitieMouse = Mouse::getPosition(window);
	dateNod nodPePozitieMouse;
	nodPePozitieMouse.x = pozitieMouse.x;
	nodPePozitieMouse.y = pozitieMouse.y;

	for (auto& A : listaArbori)
	{
		nod* nodGasit = gasesteNodInArbore(A, nodPePozitieMouse);
		if (nodGasit != nullptr)
		{
			return nodGasit;
		}
	}
	return nullptr;
}

nod* gasesteNodInListaArbori(const dateNod& date) {

	for (auto A : listaArbori)
	{
		nod* nodGasit = gasesteNodInArbore(A, date);
		if (nodGasit != nullptr)
			return nodGasit;
	}
	return nullptr;
}


int numaraNoduri(const nod* N) {
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
	int poz = -1;
	for (int i = 0; i < listaArbori.size(); i++)
		if (esteNodInArbore(N, listaArbori[i].radacina))
			poz = i;
	if (poz == -1)
		return;
	
	//nu uita de stergere ceva nod listaArbori[i]...
	stergereIntregArbore(N->st);
	stergereIntregArbore(N->dr);

	N = nullptr;
	delete N;
}

void stergereArboreCuRadacina(arbore& A) {
	if (A.radacina == nullptr)
		return;
	stergereIntregArbore(A.radacina);
	initializareArbore(A);
}

void stergereDinListaArbori(nod* N)
{
	for (int i = 0; i < listaArbori.size();) {
		if (listaArbori[i].radacina == N || listaArbori[i].radacina==nullptr) {
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
		SubarboreNou.nrNoduri = numarNoduriDinArbore(SubarboreNou);
		listaArbori.insert(listaArbori.begin(), SubarboreNou);
	}

	if (subarbore2 != nullptr) {
		arbore SubarboreNou;
		atribuireArbore(SubarboreNou, subarbore2->date);
		SubarboreNou.nrNoduri = numarNoduriDinArbore(SubarboreNou);
		listaArbori.insert(listaArbori.begin(), SubarboreNou);
	}
	stergereDinListaArbori(N);
	stergereIntregArbore(N);
}

bool existaLinie(const pair<dateNod, dateNod>& linie) {
	for (const auto& L : listaLinii)
	{
		if (linie.first.x == L.first.x
			&& linie.first.y == L.first.y
			&& linie.second.x == L.second.x
			&& linie.second.y == L.second.y)
			return true;
	}
	return false;
}

bool creareLegatura(nod*& nod1, nod*& nod2) {
	if (nod1 == nullptr || nod2 == nullptr)
		return false;
	if ((nod1->date.tip==5 && nod1->dr != nullptr)
	  ||(nod1->date.tip!=5 && (nod1->st != nullptr || nod1->dr != nullptr)))
		return false;

	pair<dateNod, dateNod> linie1 = make_pair(nod1->date, nod2->date);
	pair<dateNod, dateNod> linie2 = make_pair(nod2->date, nod1->date);

	if (existaLinie(linie1) || existaLinie(linie2))
		return false;

	int poz = -1;
	for (int i = 0; i < listaArbori.size(); i++)
		if (listaArbori[i].radacina == nod2) {
			poz = i;
			break;
		}
	if (poz == -1)
		return false;

	for (auto& i : listaArbori)
		if (esteNodInArbore(nod1, i.radacina)) {
			if (esteNodInArbore(nod2, i.radacina))//nod2 != listaArbori[i].radacina && 
				return false;

			listaLinii.push_back(linie1);
			if (nod1->date.tip == 5)
			{
				if (nod1->st == nullptr)
					nod1->st = nod2;
				else
					nod1->dr = nod2;
			}
			else {
				nod1->st = nod2;
			}
			i.nrNoduri = numaraNoduri(i.radacina);
			stergereDinListaArbori(nod2);
			
			return true;
		}
	return false;
}

