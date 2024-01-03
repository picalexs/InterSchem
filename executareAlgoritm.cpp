#include "executareAlgoritm.h"

#include "desenareSimboluri.h"
#include "evaluareExpresie.h"
#include "logicaSimboluri.h"

bool nrStartStop(int& nrStart, int& nrStop, const Nod* N, unordered_set<const Nod*>& noduriVizitate)
{
	if (N == nullptr || noduriVizitate.count(N))
		return true;
	noduriVizitate.insert(N);
	if (N->date.tip == TipNod::START) {
		nrStart++;
		if (nrStart > 1) {//am mai mult de un Nod start
			const string eroare = "Eroare: Are mai mult de un Nod start!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	else if (N->date.tip == TipNod::STOP) {
		nrStop++;
		if (N->st != nullptr || N->dr != nullptr) {//nodul stop nu are voie sa aiba fii
			const string eroare = "Eroare: Are Nod stop ca fiu!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	else if (N->dr == nullptr && N->st == nullptr)//se afla un Nod diferit de 1 ca frunza
	{
		const string eroare = "Eroare: Lipseste un Nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return nrStartStop(nrStart, nrStop, N->st, noduriVizitate) && nrStartStop(nrStart, nrStop, N->dr, noduriVizitate);
}

bool verificareStartStop(const Nod* radacina)
{
	unordered_set<const Nod*> noduriVizitate;
	int nrStart = 0, nrStop = 0;
	if (!nrStartStop(nrStart, nrStop, radacina, noduriVizitate))
		return false;
	if (nrStop == 0 || nrStart == 0) {
		const string eroare = "Eroare: Nu are Nod start sau Nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return true;
}

bool esteAlgoritmCorect()
{
	if (listaArbori.empty() || listaArbori.size() > 1) {
		const string eroare = "Eroare: Nu are forma buna! Nu are exact un \"arbore\" de parcurs";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	if (listaArbori[0].radacina == nullptr)
		return false;
	if (listaArbori[0].radacina->date.tip != TipNod::START)
	{
		const string eroare = "Eroare: Nu are Nod start la inceput!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	if (!verificareStartStop(listaArbori[0].radacina))
		return false;
	cout << "Are forma buna!\n";
	return true;
}

Nod* passParcurgere(Nod* N)
{
	if (N == nullptr)
		return nullptr;
	switch (N->date.tip)
	{
	case TipNod::START:
		return N->st;
	case TipNod::STOP:
		return nullptr;
	case TipNod::ATRIBUIRE:
		logicaAtribuire(N);
		return N->st;
	case TipNod::CITIRE:
		logicaCitire(N);
		return N->st;
	case TipNod::AFISARE:
		logicaAfisare(N);
		return N->st;
	case TipNod::DACA:
	case TipNod::WHILE:
		if (logicaDaca(N)) {
			return N->st;
		}
		return N->dr;
	case TipNod::NEDEFINIT:
		cout << "NOD NEDEFINIT!!\n";
	}
	return nullptr;
}

bool seParcurge = false;
Nod* ultimNodParcurs = nullptr;
Nod* nodParcurgere = nullptr;
void executareAlgoritm()
{
	if (seParcurge == false) {
		if (!esteAlgoritmCorect())
			return;
		nodParcurgere = listaArbori[0].radacina;
		seParcurge = true;
	}
	cout << "Executare nod cu expresia: " << nodParcurgere->date.expresie << '\n';
	ultimNodParcurs = nodParcurgere;
	nodParcurgere = passParcurgere(nodParcurgere);
	if (nodParcurgere == nullptr)
	{
		seParcurge = false;
		cout << "S-a terminat executarea algoritmului!\n";
	}
}

bool seParcurgeAlgoritmul()
{
	return seParcurge;
}

Nod* nodCurentDeParcurgere()
{
	return ultimNodParcurs;
}


