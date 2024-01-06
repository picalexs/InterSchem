#include "functiiNod.h"
#include "convertireCPlusPlus.h"
#include <fstream>

using namespace std;
ofstream fout("output.txt");
int nrStart = 0, nrStop = 0;
/*void nrStartStop(Arbore A, const DateNod& date)
{
	int ok = 1;
	if (listaArbori.size() > 1)
		ok = 0;
	verificare(A.radacina, date);
	if (nrStop != 1)
		ok = 0;
	if (ok == 1)
	{
		cout << "#include <iostream>" << '\n';
		cout << "using namespace std;" << '\n';

		parcurgere(A.radacina, date);

	}
}*/
bool nrStartStop(int& nrStart, int& nrStop, const Nod* nodCurent)
{
	if (listaArbori.size() > 1)
	{
		const string eroare = "Exista mai mult de o schema logica!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	if (nodCurent == nullptr)
		return true;
	if (nodCurent->date.tip == TipNod::START)
	{
		nrStart++;
		if (nrStart > 1)
		{
			const string eroare = "Exista mai mult de un Nod start!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	if (nodCurent->date.tip == TipNod::STOP)
	{
		nrStop++;
		if (nodCurent->st != nullptr || nodCurent->dr != nullptr)
		{
			const string eroare = "Nodul STOP nu poate avea fii!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	if (nodCurent->st == nullptr || nodCurent->dr == nullptr)
	{
		const string eroare = "Nu exista niciun nod STOP!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return nrStartStop(nrStart, nrStop, nodCurent->st) && nrStartStop(nrStart, nrStop, nodCurent->dr);
}
bool verificare(const Nod* radacina)
{
	int nrStart=0, nrStop=0;
	if (nrStartStop(nrStart, nrStop, radacina) == 0)
		return false;
	if (nrStart == 0 || nrStop == 0)
	{
		const string eroare = "Nu exista niciun nod STOP sau START!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return true;
}

void parcurgere(Nod* nodCurent, unordered_set<const Nod*>& noduriVizitate)
{
	if (nodCurent == nullptr)
		return;
	if (nodCurent->date.tip == TipNod::START)
	{
		noduriVizitate.insert(nodCurent);
		parcurgere(nodCurent->st, noduriVizitate);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		noduriVizitate.insert(nodCurent);
		fout << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, noduriVizitate);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		noduriVizitate.insert(nodCurent);
		fout << "int " << nodCurent->date.expresie<<';' << '\n';
		fout << "cin>>" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, noduriVizitate);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		noduriVizitate.insert(nodCurent);
		fout << "cout<<" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, noduriVizitate);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		noduriVizitate.insert(nodCurent);
		fout << "if(" << nodCurent->date.expresie << ")"<<'\n';
		fout << "{"<<'\n';
		parcurgere( nodCurent->st, noduriVizitate);
		fout << "}";
		fout << '\n' << "else"<<'\n';
		fout << "{" << '\n';
		parcurgere(nodCurent->dr, noduriVizitate);
		fout << "}";
	}
	if (nodCurent->date.tip == TipNod::WHILE)
	{
		noduriVizitate.insert(nodCurent);
		cout << "if(" << nodCurent->date.expresie << ")" << '\n';
		cout << "{" << '\n';
		unordered_set<const Nod*>::iterator I = noduriVizitate.find(nodCurent->st);
		if (I == noduriVizitate.end())
		   parcurgere(nodCurent->st, noduriVizitate);
		else
		{
			cout << "}";
			parcurgere(nodCurent->dr, noduriVizitate);
		}
	}
}

/*void convertire()
{

}*/