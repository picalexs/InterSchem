#include "convertireCPlusPlus.h"
using namespace std;

string codConvertit;
int nrStart = 0, nrStop = 0;
int nrAcolade = 0;

string getCodConvertit()
{
	return codConvertit;
}

int nrSpatii = 1;

void convertireInCodRec(const Nod* nodCurent, const RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	int i;
	static set<const Nod*> noduriVizitate;
	static string s;
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent) != 0)
		return;
	noduriVizitate.insert(nodCurent);
	if (nodCurent->date.tip == TipNod::START)
	{
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "float " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "cin>> " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		int nrG = 0;
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "cout << ";
		s += nodCurent->date.expresie;
		for (i = 0; i < s.size(); i++)
		{
			if (s[i] == '"')
			{
				nrG++;
				if (nrG % 2 == 0 && i != s.size() - 1) ///daca am ghilimele inchise si daca n am ajuns la final
				{
					codConvertit += s[i];
					codConvertit += " <<";
				}
				else
					codConvertit += s[i];
			}
			else
				if (s[i + 1] == '"' && s[i-1]!='"' && nrG % 2 == 0) ///verific daca urmeaza ghilimele si daca nu au fost deja
				{
					codConvertit += " <<";
					codConvertit += s[i];
				}
			else
			codConvertit += s[i];
		}
		codConvertit += ";\n";
		///codConvertit += "cout<< " + nodCurent->date.expresie + ";\n";
		s.clear();
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		for (i = 1; i <= nrSpatii; i++)
			 codConvertit += ' ';
		codConvertit += "if(" + nodCurent->date.expresie + ")" + "\n";
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "{\n";
		nrSpatii += 4;
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		nrSpatii -= 4;
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "}\n";
		if (nodCurent->dr->date.tip!=TipNod::STOP)
		{
			for (i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "else\n";
			for (i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "{\n";
			nrSpatii += 4;
			convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
			nrSpatii -= 4;
			for (i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "}\n";
		}
	}
	if (nodCurent->date.tip == TipNod::WHILE)
	{
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "while(" + nodCurent->date.expresie + ")" + "\n";
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "{\n";
		nrSpatii += 4;
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		nrSpatii -= 4;
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "}\n";

		convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
	}
	noduriVizitate.clear();
}

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	int i;
	codConvertit.clear();
	if (!esteAlgoritmCorect())
		return;
	codConvertit += "#include <iostream>\n";
	codConvertit += "#include <cmath>\n";
	codConvertit += "using namespace std;\n";
	codConvertit += "#int main()\n";
	codConvertit += "{\n";

	convertireInCodRec(listaArbori[0].radacina, fereastraAplicatie, desktop);

	for (i = 1; i <= nrSpatii; i++)
		codConvertit += ' ';

	codConvertit += "return 0;\n";
	codConvertit += "}\n";

	cout << "Codul a fost convertit!\n";

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	Text mainText(codConvertit, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	mainText.setPosition(71 * desktop.width / 100, 20 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}
