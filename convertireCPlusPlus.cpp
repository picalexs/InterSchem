#include "functiiNod.h"
#include "convertireCPlusPlus.h"
#include "executareAlgoritm.h"
#include <set>
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
		fout << "#include <iostream>" << '\n';
		fout << "using namespace std;" << '\n';

		parcurgere(A.radacina, date);

	}
}*/
bool nrStartStop(int& nrStart, int& nrStop, const Nod * nodCurent)
{
	if (listaArbori.size() > 1)
	{
		const string eroare = "Exista mai mult de o schema logica!";
		fout << eroare << '\n';
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
			fout << eroare << '\n';
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
			fout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
	}
	if (nodCurent->st == nullptr || nodCurent->dr == nullptr)
	{
		const string eroare = "Nu exista niciun nod STOP!";
		fout << eroare << '\n';
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
		fout << eroare << '\n';
		listaConsola.push_back(eroare);
		return false;
	}
	return true;
}

int k = 0;
void parcurgere(Nod* nodCurent, RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	static set<const Nod*> noduriVizitate;
	k++;
	if (nodCurent == nullptr)
		return;
	if (noduriVizitate.count(nodCurent) != 0)
		return;
	if (nodCurent->date.tip == TipNod::START)
	{
		noduriVizitate.insert(nodCurent);
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		///fout<<"int "<< nodCurent->date.expresie << ';' << '\n';
		noduriVizitate.insert(nodCurent);

		const int marimeFont = static_cast<int>(desktop.width) / 90;
		Text mainText(nodCurent->date.expresie, fontGlobal, marimeFont);
		mainText.setFillColor(Color::Black);
		const FloatRect marginiText = mainText.getLocalBounds();
		mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
		mainText.setPosition(73 * desktop.width / 100, (k*5+23) * desktop.height / 100);
		fereastraAplicatie.draw(mainText);

		fout << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		noduriVizitate.insert(nodCurent);
		fout << "int " << nodCurent->date.expresie<<';' << '\n';
		fout << "cin>>" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		noduriVizitate.insert(nodCurent);
		fout << "fout<<" << nodCurent->date.expresie<<';'<<'\n';
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		noduriVizitate.insert(nodCurent);
		fout << "if(" << nodCurent->date.expresie << ")"<<'\n';
		fout << "{"<<'\n';
		parcurgere( nodCurent->st, fereastraAplicatie, desktop);
		fout << "}";
		fout << '\n' << "else"<<'\n';
		fout << "{" << '\n';
		parcurgere(nodCurent->dr, fereastraAplicatie, desktop);
		fout << "}"<<'\n';
	}
	if (nodCurent->date.tip == TipNod::WHILE)
	{
		noduriVizitate.insert(nodCurent);
		fout << "while(" << nodCurent->date.expresie << ")" << '\n';
		fout << "{" << '\n';
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
		fout << "}"<<'\n';
		parcurgere(nodCurent->dr, fereastraAplicatie, desktop);
	}
	noduriVizitate.clear();
}

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	if (!esteAlgoritmCorect())
		return;
	fout << "#include <iostream>" << '\n';
	fout << "include <cmath>"<<'\n';
	fout << "using namespace std;" << '\n';
	fout << "int main(){" << '\n';

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	Text mainText("#include <iostream> \n #include <cmath> \n using namespace std; \n int main(){", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(77 * desktop.width / 100, 23 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);

	parcurgere(listaArbori[0].radacina, fereastraAplicatie, desktop);
	fout << "return 0" << '\n';
	fout << "}";

}
