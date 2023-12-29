#include "executareAlgoritm.h"
#include "evaluareExpresie.h"
#include "logicaSimboluri.h"

bool nrStartStop(int& nrStart, int& nrStop, const nod* N)
{
	if (N == nullptr)
		return true;
	if (N->date.tip == 0) {
		nrStart++;
		if (nrStart > 1) {//am mai mult de un nod start
			const string eroare = "Eroare: Are mai mult de un nod start!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	else if (N->date.tip == 1) {
		nrStop++;
		if (N->st != nullptr || N->dr != nullptr) {//nodul stop nu are voie sa aiba fii
			const string eroare = "Eroare: Are nod stop ca fiu!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	else if (N->dr == nullptr && N->st == nullptr)//se afla un nod diferit de 1 ca frunza
	{
		const string eroare = "Eroare: Lipseste un nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return nrStartStop(nrStart, nrStop, N->st) && nrStartStop(nrStart, nrStop, N->dr);
}

bool verificareStartStop(const nod* radacina)
{
	int nrStart = 0, nrStop = 0;
	if (!nrStartStop(nrStart, nrStop, radacina))
		return false;
	if (nrStop == 0 || nrStart == 0) {
		const string eroare = "Eroare: Nu are nod start sau nod stop!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return true;
}

bool verificareAlgoritm()
{
	if (listaArbori.empty() || listaArbori.size() > 1) {
		const string eroare = "Eroare: Nu are forma buna! Nu are exact un \"arbore\" de parcurs";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	if (listaArbori[0].radacina == nullptr)
		return false;
	if (listaArbori[0].radacina->date.tip != 0)
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

void parcurgereAlgoritm(nod* N)
{
	if (N == nullptr)
		return;
	switch (N->date.tip)
	{
	case 0:
		parcurgereAlgoritm(N->st);
		return;
	case 1:
		return;
	case 2:
		logicaAtribuire(N);
		parcurgereAlgoritm(N->st);
		return;
	case 3:
		logicaCitire(N);
		parcurgereAlgoritm(N->st);
		return;
	case 4:
		logicaAfisare(N);
		parcurgereAlgoritm(N->st);
		return;
	case 5:
		if (logicaDaca(N)) {
			parcurgereAlgoritm(N->st);
		}
		else {
			parcurgereAlgoritm(N->dr);
		}
	}
}

bool esteParcurgereaActiva = false;
void executareAlgoritm()
{
	if (!verificareAlgoritm())//daca nu are forma corecta iesim.
		return;
	esteParcurgereaActiva = true;
	parcurgereAlgoritm(listaArbori[0].radacina);
	esteParcurgereaActiva = false;
}

bool seParcurgeAlgoritmul()
{
	return esteParcurgereaActiva;
}
