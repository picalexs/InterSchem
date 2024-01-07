#include "functiiNod.h"
#include "convertireCPlusPlus.h"
#include "executareAlgoritm.h"
#include <set>
///#include <fstream>

using namespace std;
///ofstream cout("output.txt");
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
bool nrStartStop(int& nrStart, int& nrStop, const Nod * nodCurent)
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


void parcurgere(Nod* nodCurent)
{
	static set<const Nod*> noduriVizitate;
	if (nodCurent == nullptr)
		return;
	if (noduriVizitate.count(nodCurent) != 0)
		return;
	if (nodCurent->date.tip == TipNod::START)
	{
		noduriVizitate.insert(nodCurent);
		parcurgere(nodCurent->st);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		///cout<<"int "<< nodCurent->date.expresie << ';' << '\n';
		noduriVizitate.insert(nodCurent);
		cout << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		noduriVizitate.insert(nodCurent);
		cout << "int " << nodCurent->date.expresie<<';' << '\n';
		cout << "cin>>" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		noduriVizitate.insert(nodCurent);
		cout << "cout<<" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		noduriVizitate.insert(nodCurent);
		cout << "if(" << nodCurent->date.expresie << ")"<<'\n';
		cout << "{"<<'\n';
		parcurgere( nodCurent->st);
		cout << "}";
		cout << '\n' << "else"<<'\n';
		cout << "{" << '\n';
		parcurgere(nodCurent->dr);
		cout << "}"<<'\n';
	}
	if (nodCurent->date.tip == TipNod::WHILE)
	{
		noduriVizitate.insert(nodCurent);
		cout << "while(" << nodCurent->date.expresie << ")" << '\n';
		cout << "{" << '\n';
		parcurgere(nodCurent->st);
		cout << "}"<<'\n';
		parcurgere(nodCurent->dr);
	}
	noduriVizitate.clear();
}

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	if (!esteAlgoritmCorect())
		return;
	cout << "#include <iostream>" << '\n';
	cout << "include <cmath>"<<'\n';
	cout << "using namespace std;" << '\n';
	cout << "int main(){" << '\n';

	parcurgere(listaArbori[0].radacina);
	cout << "return 0" << '\n';
	cout << "}";

}
