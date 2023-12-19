#include "functiiNod.h"
#include "convertireCPlusPlus.h"

int nrStart = 0, nrStop = 0;
void nrStartStop(arbore A, RenderWindow& window, const dateNod& date)
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
}
void verificare(nod* nodCurent, const dateNod& date)
{
	if (nodCurent == nullptr)
		return;
	if (nodCurent->date.tip == 0)
		nrStart++;
	else
		if (nodCurent->date.tip == 1)
			nrStop++;
	verificare(nodCurent->dr, date);
	verificare(nodCurent->st, date);
}

void parcurgere(nod* nodCurent, const dateNod& date)
{
	if (nodCurent == nullptr)
		return;
	if (nodCurent->date.tip == 2)
		cout << nodCurent->date.expresie;
	if (nodCurent->date.tip == 3)
		cout<<"cin>>"<<nodCurent->date.expresie;
	if (nodCurent->date.tip == 3)
		cout << "cout<<" << nodCurent->date.expresie;
	if (nodCurent->date.tip == 3)
		cout << "if()" << nodCurent->date.expresie;
	parcurgere(nodCurent->st, date);
	parcurgere(nodCurent->dr, date);
}