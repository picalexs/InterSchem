#include "executareAlgoritm.h"
#include "evaluareExpresie.h"

bool nrStartStop(int& nrStart, int& nrStop, const nod* N)
{
	if (N == nullptr)
		return true;
	if (N->date.tip == 0) {
		nrStart++;
		if (nrStart > 1) {//am mai mult de un nod start
			cout << "Eroare: Are mai mult de un nod start!" << endl;
			return false;
		}
	}
	else if (N->date.tip == 1) {
		nrStop++;
		if (N->st != nullptr || N->dr != nullptr) {//nodul stop nu are voie sa aiba fii
			cout << "Eroare: Are nod stop ca fiu!" << endl;
			return false;
		}
	}

	return nrStartStop(nrStart, nrStop, N->st) && nrStartStop(nrStart, nrStop, N->dr);
}

bool verificareStartStop(const nod* radacina)
{
	int nrStart = 0, nrStop = 0;
	if (!nrStartStop(nrStart, nrStop, radacina))
		return false;
	if (nrStop == 0 || nrStart == 0) {
		cout << "Eroare: Nu are nod start sau nod stop!" << endl;
		return false;
	}
	return true;
}

bool verificareAlgoritm()
{
	if (listaArbori.empty() || listaArbori.size() > 1) {
		cout << "Nu are forma buna! Nu are un singur \"arbore\" de parcurs" << endl;
		return false;
	}
	if (listaArbori[0].radacina == nullptr)
		return false;
	if (listaArbori[0].radacina->date.tip != 0)
	{
		cout << "Eroare: Nu are nod start la inceput!" << endl;
		return false;
	}
	if (!verificareStartStop(listaArbori[0].radacina))
		return false;
	cout << "Are forma buna!" << endl;
	return true;
}

void executareAlgoritm()
{
	if (!verificareAlgoritm())
		return;
}
