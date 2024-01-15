#include "convertireCPlusPlus.h"

using namespace std;

string codConvertit;
int nrStart = 0, nrStop = 0;
int nrAcolade = 0;

string getCodConvertit()
{
	return codConvertit;
}

int nrSpatii = 5;

void convertireInCodRec(const Nod* nodCurent, const RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{

	static set<const Nod*> noduriVizitate;
	static set<string> variabileConvertire;
	static set <string> vectorConvertire;
	if (noduriVizitate.count(nodCurent) != 0 && nodCurent->date.tip == TipNod::CAT_TIMP)
		return;
	if (nodCurent == nullptr)
	{
		noduriVizitate.clear();
		return;
	}
	noduriVizitate.insert(nodCurent);
	if (nodCurent->date.tip == TipNod::START)
	{
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		int i;
		for (i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		string s;
		string variabila;
		string atribuire;
		string vectorAtribuire;
		s += nodCurent->date.expresie;
		bool ok = false;

		for (i = 0; i < s.size() && ok == false; i++) {
			if (s[i] != '=') {
				variabila += s[i];
			}
			else {
				ok = true;
			}
		}
		atribuire += '=';
		for (int j = i; j < s.size(); j++) {
			atribuire += s[j];
		}

		int gasit = 0;
		for (i = 0; i < variabila.size() && gasit==0; i++)
			if (variabila[i] == '[')
			{
				if (vectorConvertire.find(vectorAtribuire) != vectorConvertire.end())
					codConvertit += variabila + atribuire + ";\n";
				else
				{
					gasit = 1;
					vectorConvertire.insert(vectorAtribuire);
					cout << variabila << ' ' << atribuire << ' ';
					///codConvertit+= "float " +variabila+"={0}" + "; \n";
					codConvertit += "float " + vectorAtribuire + '[';
					i++;
					while (variabila[i] != ']' && i<variabila.size())
					{
						codConvertit += variabila[i];
						i++;
					}
					codConvertit += "]={0}";
				}
			}
			else
				vectorAtribuire += variabila[i];
		if (gasit == 1)
		{
			while (i < variabila.size())
			{
				codConvertit += variabila[i];
				i++;
			}
			if (atribuire.size() > 1)
				codConvertit += atribuire + ";\n";
			else
				codConvertit += ";\n";
		}
		if (vectorAtribuire.compare(variabila) == 0)
			if (variabileConvertire.find(variabila) != variabileConvertire.end())
			{
				codConvertit += variabila + atribuire + ";\n";
			}
			else
			{
				variabileConvertire.insert(variabila);
				cout << variabila << ' ' << atribuire << ' ';
				codConvertit += "float " + variabila + atribuire + ";\n";
			}
		///codConvertit += "float " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "cin>> " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		int nrG = 0;
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "cout << ";
		string s;
		s += nodCurent->date.expresie;
		for (int i = 0; i < s.size(); i++)
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
				if (s[i + 1] == '"' && s[i - 1] != '"' && nrG % 2 == 0) ///verific daca urmeaza ghilimele si daca nu au fost deja
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
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "if(" + nodCurent->date.expresie + ")" + "\n";
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "{\n";
		nrSpatii += 4;
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		nrSpatii -= 4;
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "}\n";
		if (nodCurent->dr->date.tip != TipNod::STOP)
		{
			for (int i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "else\n";
			for (int i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "{\n";
			nrSpatii += 4;
			convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
			nrSpatii -= 4;
			for (int i = 1; i <= nrSpatii; i++)
				codConvertit += ' ';
			codConvertit += "}\n";
		}
	}
	if (nodCurent->date.tip == TipNod::CAT_TIMP)
	{
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "while(" + nodCurent->date.expresie + ")" + "\n";
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "{\n";
		nrSpatii += 4;
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		nrSpatii -= 4;
		for (int i = 1; i <= nrSpatii; i++)
			codConvertit += ' ';
		codConvertit += "}\n";

		convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
	}
	variabileConvertire.clear();
	vectorConvertire.clear();
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
	codConvertit += "int main()\n";
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
	///if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		///view.move(0, -5);
		fereastraAplicatie.draw(mainText);
	///}
	
}
