#include "logicaExecutare.h"
#include "evaluareExpresie.h"
#include "functiiMatematice.h"
#include "functiiNod.h"
#include "functiiExpresie.h"

//caute expresii de tipul "var1 = expr1" sau "var1 = expr1, var2 = expr2, ..." si le salveaza in map-ul "variabile"
void logicaAtribuire(Nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;
	string expresie = N->date.expresie;
	stergereSpatii(expresie);
	string expresieDeCitit;
	int nrVariabile = 0, nrVirgule = 0;

	size_t i = 0;
	while (i < expresie.size())
	{
		const size_t pozitieEgal = expresie.find('=', i);
		if (pozitieEgal == string::npos)
		{
			const string eroare = "Eroare la atribuire! Expresia nu contine '='!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return;
		}
		string numeVariabila = expresie.substr(i, pozitieEgal - i);
		for (const char ch : numeVariabila)
			if (!isalnum(ch))
			{
				const string eroare = "Eroare la atribuire! Numele variabilei nu este corect!";
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return;
			}
		nrVariabile++;
		i = pozitieEgal + 1;

		const size_t pozitieVirgula = expresie.find(',', i);
		if (pozitieVirgula != string::npos)
		{
			expresieDeCitit = expresie.substr(i, pozitieVirgula - i);
			i = pozitieVirgula + 1;
			nrVirgule++;
		}
		else
		{
			expresieDeCitit = expresie.substr(i);
			if (expresieDeCitit == "\r")
			{
				const string eroare = "Eroare la atribuire! Expresia este goala!";
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return;
			}
			i = expresie.size();
		}

		const long double rezultat = evaluareExpresie(expresieDeCitit);
		if (!isnan(rezultat))
		{
			seteazaVariabila(numeVariabila, rezultat);
		}
		else
		{
			string eroare = "Eroare la atribuire! Expresia este gresita!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
		}
	}
	//sterge ultima virgula daca e in plus
	if (nrVariabile == nrVirgule)
	{
		for (size_t i = expresie.size() - 1; i > 0; i--)
			if (expresie[i] == ',')
			{
				expresie.erase(i, 1);
				N->date.expresie = expresie;
				return;
			}
	}
}
bool seCiteste = false;
string numeVariabila;
void logicaCitire(const Nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;
	numeVariabila = N->date.expresie;
	stergereSpatii(numeVariabila);
	for (char i : numeVariabila)
		if (!isalnum(i))
		{
			const string eroare = "Eroare la citire! Numele variabilei nu este corect!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return;
		}
	seCiteste = true;
}

bool seCitestePtParcurgere()
{
	return seCiteste;
}

string getNumeVariabila()
{
	return numeVariabila;
}

void logicaAfisare(Nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;

	string expresie = N->date.expresie;
	string output, numeVariabila;

	bool ghilimele = false;
	for (size_t i = 0; i < expresie.size(); i++)
	{
		char ch = expresie[i];
		string opL = expresie.substr(i, 2);
		if (!ghilimele && esteOperatorLung(opL))
		{
			numeVariabila += opL;
			i += 1;
		}
		else if ((!ghilimele && (isalnum(ch) || ch == ' ' || ch == ')' || ch == '(' || esteOperator(ch)))
			|| (ghilimele && (ch > 31 && ch < 127 && ch != 34)))
		{
			numeVariabila += ch;
		}
		else
		{
			if (!ghilimele)
			{
				if (!numeVariabila.empty())
				{
					long double rezultat = evaluareExpresie(numeVariabila);
					if (!isnan(rezultat))
					{
						stringstream stream;
						stream << defaultfloat << setprecision(6) << rezultat;
						output += stream.str();
						numeVariabila.clear();
					}
				}
			}
			else
			{
				output += numeVariabila;
				numeVariabila.clear();
			}
			if (ch == '"')
			{
				ghilimele = !ghilimele;
			}
		}
	}
	if (!ghilimele)
	{
		if (!numeVariabila.empty())
		{
			long double rezultat = evaluareExpresie(numeVariabila);
			if (!isnan(rezultat))
			{
				stringstream stream;
				stream << defaultfloat << setprecision(6) << rezultat;
				output += stream.str();
				numeVariabila.clear();
			}
		}
	}
	cout << "S-a adaugat: " << output << " in lista de output" << endl;
	listaConsola.push_back(output);
}


bool logicaDaca(Nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return false;
	const long double rezultat = evaluareExpresie(N->date.expresie);
	if (static_cast<bool>(rezultat))
		return true;
	return false;
}
