#include "executareAlgoritm.h"

#include "desenareLinie.h"
#include "desenareSimboluri.h"
#include "evaluareExpresie.h"
#include "logicaExecutare.h"
#include "logicaSimboluri.h"

bool nrStartStop(int& nrStart, int& nrStop, const Nod* N, set<const Nod*>& noduriVizitate)
{
	if (N == nullptr || noduriVizitate.count(N))
		return true;
	noduriVizitate.insert(N);
	if (N->date.tip == TipNod::START) {
		nrStart++;
		if (nrStart > 1) {//am mai mult de un Nod start
			const string eroare = "Eroare: Are mai mult de un nod start!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	else if (N->date.tip == TipNod::CAT_TIMP || N->date.tip == TipNod::DACA)
	{
		if (N->st == nullptr || N->dr == nullptr) {
			const string eroare = "Eroare: Are un nod DACA/CAT TIMP cu mai putin de 2 fii!";
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
	else if (N->dr == nullptr && N->st == nullptr)//se afla un Nod diferit de stop ca frunza
	{
		const string eroare = "Eroare: Lipseste un nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return nrStartStop(nrStart, nrStop, N->st, noduriVizitate) && nrStartStop(nrStart, nrStop, N->dr, noduriVizitate);
}

bool verificareStartStop(const Nod* radacina)
{
	set<const Nod*> noduriVizitate;
	int nrStart = 0, nrStop = 0;
	if (!nrStartStop(nrStart, nrStop, radacina, noduriVizitate))
		return false;
	if (nrStop == 0 || nrStart == 0) {
		const string eroare = "Eroare: Nu are nod start sau Nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return true;
}

bool esteAlgoritmCorect()
{
	if (listaArbori.empty() || listaArbori.size() > 1) {
		const string eroare = "Eroare: Nu are forma buna! Nu are exact un drum de parcurs";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	if (listaArbori[0].radacina == nullptr)
		return false;
	if (listaArbori[0].radacina->date.tip != TipNod::START)
	{
		const string eroare = "Eroare: Nu are nod start la inceput!";
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
	case TipNod::CAT_TIMP:
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
Nod* antepenultimNodParcurs = nullptr;
Nod* nodParcurgere = nullptr;

void executareAlgoritmPasCuPas()
{
	if (seParcurge == false) {
		if (!esteAlgoritmCorect())
			return;
		listaConsola.clear();
		nodParcurgere = listaArbori[0].radacina;
		seParcurge = true;
	}
	cout << "Executare nod cu expresia: " << nodParcurgere->date.expresie << '\n';
	antepenultimNodParcurs = ultimNodParcurs;
	ultimNodParcurs = nodParcurgere;
	nodParcurgere = passParcurgere(nodParcurgere);
	if (antepenultimNodParcurs != nullptr && ultimNodParcurs != nullptr) {
		const unsigned idLinie = existaLinie(antepenultimNodParcurs, ultimNodParcurs);
		if (idLinie != -1)
			liniiDeDesenat[idLinie].culoareLinie = Color(255, 134, 20);
		//coloreaza linia de la ultimul simbol la cel curent
	}
	if (nodParcurgere == nullptr)
	{
		seParcurge = false;
		variabile.clear();
		reseteazaCuloareLinii();
		atribuireConstanteCunoscute();
		cout << "S-a terminat executarea algoritmului!\n";
	}
}

float vitezaDeRulare = 0.5f;
void executareTotAlgoritm()
{
	static Clock ceas;
	const Time timp = ceas.getElapsedTime();
	if (timp.asSeconds() > vitezaDeRulare)
	{
		executareAlgoritmPasCuPas();
		ceas.restart();
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


void updateazaValoareVitezaDeRulare(float valoare)
{
	vitezaDeRulare = valoare;
}
