#include "functiiNod.h"
#include "convertireCPlusPlus.h"
#include "executareAlgoritm.h"
#include <set>
#include <cstdio>

using namespace std;
string codConvertit;
int nrStart = 0, nrStop = 0;
int nrAcolade = 0;
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

		noduriVizitate.insert(nodCurent);
		codConvertit+="float "+ nodCurent->date.expresie + ";\n";

		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		noduriVizitate.insert(nodCurent);
		codConvertit +="cin>> "+ nodCurent->date.expresie + ";\n";
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		noduriVizitate.insert(nodCurent);
		codConvertit +="cout<< " +nodCurent->date.expresie + ";\n";
		
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		noduriVizitate.insert(nodCurent);
		codConvertit += "if("+nodCurent->date.expresie +")" + "\n";
		codConvertit += "{\n";
		
		parcurgere( nodCurent->st, fereastraAplicatie, desktop);
		codConvertit += "}\n";
		codConvertit += "else\n";
		codConvertit += "{\n";
		
		parcurgere(nodCurent->dr, fereastraAplicatie, desktop);
		codConvertit += "}\n";
	}
	if (nodCurent->date.tip == TipNod::WHILE)
	{
		noduriVizitate.insert(nodCurent);
		codConvertit += "while(" + nodCurent->date.expresie + ")" + "\n";
		codConvertit += "{\n";
		
		parcurgere(nodCurent->st, fereastraAplicatie, desktop);

		codConvertit += "}\n";
		
		parcurgere(nodCurent->dr, fereastraAplicatie, desktop);
	}
	noduriVizitate.clear();
}

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	codConvertit.clear();
	if (!esteAlgoritmCorect())
		return;
	codConvertit += "#include <iostream>\n";
	codConvertit += "#include <cmath>\n";
	codConvertit += "using namespace std;\n";
	codConvertit += "#int main()\n";
	codConvertit += "{\n";


	parcurgere(listaArbori[0].radacina, fereastraAplicatie, desktop); 

	codConvertit += "return 0;\n";
	codConvertit += "}\n";
	cout << '\n' << codConvertit;

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	Text mainText(codConvertit, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	mainText.setPosition(71 * desktop.width / 100, 20 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}
