#include "functiiNod.h"
#include "convertireCPlusPlus.h"

int nrStart = 0, nrStop = 0;
void nrStartStop(Arbore A, const DateNod& date)
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
void verificare(Nod* nodCurent, const DateNod& date)
{
	if (nodCurent == nullptr)
		return;
	if (nodCurent->date.tip == TipNod::START)
		nrStart++;
	else
		if (nodCurent->date.tip == TipNod::STOP)
			nrStop++;
	verificare(nodCurent->dr, date);
	verificare(nodCurent->st, date);
}

void parcurgere(Nod* nodCurent, const DateNod& date)
{
	if (nodCurent == nullptr)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		cout << nodCurent->date.expresie;
		parcurgere(nodCurent->st, date);
		parcurgere(nodCurent->dr, date);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		cout << "cin>>" << nodCurent->date.expresie;
		parcurgere(nodCurent->st, date);
		parcurgere(nodCurent->dr, date);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		cout << "cout<<" << nodCurent->date.expresie;
		parcurgere(nodCurent->st, date);
		parcurgere(nodCurent->dr, date);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		cout << "if(" << nodCurent->date.expresie << ")"<<'\n';
		cout << "{"<<'\n';
		parcurgere(nodCurent->st, date);
		cout << "}";
		cout << '\n' << "else";
		parcurgere(nodCurent->dr, date);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		cout << "if(" << nodCurent->date.expresie << ")" << '\n';
		cout << "{" << '\n';
		parcurgere(nodCurent->st, date);
		cout << "}";
		cout << '\n' << "else";
		parcurgere(nodCurent->dr, date);
	}
}