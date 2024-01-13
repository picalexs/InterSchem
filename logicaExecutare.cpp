#include "logicaExecutare.h"
#include "evaluareExpresie.h"
#include "functiiMatematice.h"
#include "functiiNod.h"
#include "functiiExpresie.h"


void setareVector(const string& expresie, string& expresieDeCitit, const string& numeElement, size_t& i, const size_t& pozitieEgal, const bool esteInitializare)
{
	const size_t pozitieParanteza = numeElement.find('[');
	const size_t pozitieParantezaInchisa = numeElement.find(']');
	const string numeVector = numeElement.substr(0, pozitieParanteza);
	string indexStr = numeElement.substr(pozitieParanteza + 1, pozitieParantezaInchisa - pozitieParanteza - 1);

	const int index = static_cast<int>(evaluareExpresie(indexStr));
	if (isnan(static_cast<long double>(index)) || index < 0)
	{
		const string eroare = "Eroare la atribuire! Index-ul vectorului nu este corect!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return;
	}

	if (!esteInitializare)
		i = pozitieEgal + 1;

	const size_t pozitieVirgula = expresie.find(',', i);
	if (pozitieVirgula != string::npos)
	{
		expresieDeCitit = expresie.substr(i, pozitieVirgula - i);
		i = pozitieVirgula + 1;
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

	if (esteInitializare)
	{
		creazaVector(numeVector, index);
	}
	else
	{
		const long double rezultat = evaluareExpresie(expresieDeCitit);
		if (!isnan(rezultat))
		{
			seteazaVector(numeVector, index, rezultat);
		}
		else
		{
			const string eroare = "Eroare la atribuire! Expresia este gresita!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
		}
	}
}

void seteazaVariabila(const string& expresie, string& expresieDeCitit, const string& numeElement, size_t& i, const size_t& pozitieEgal)
{
	const string& numeVariabila = numeElement;
	for (const char ch : numeVariabila)
	{
		if (!isalnum(ch))
		{
			const string eroare = "Eroare la atribuire! Numele variabilei nu este corect!";
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return;
		}
	}
	i = pozitieEgal + 1;

	// Gasete pozitia virgulei (',') dupa '='
	const size_t pozitieVirgula = expresie.find(',', i);
	if (pozitieVirgula != string::npos)
	{
		expresieDeCitit = expresie.substr(i, pozitieVirgula - i);
		i = pozitieVirgula + 1;
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
		const string eroare = "Eroare la atribuire! Expresia este gresita!";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
	}
}

//caute expresii de tipul "var1 = expr1" sau "var1 = expr1, var2 = expr2, ..." si le salveaza in map-ul "variabile"
//in plus initializeaza si vectori: vect[idx], sau seteaza o valoare a unui vector: vect[idx]=expresie
void logicaAtribuire(Nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;

	string expresie = N->date.expresie;
	stergereSpatii(expresie);
	string expresieDeCitit;

	size_t i = 0;
	while (i < expresie.size())
	{
		const size_t pozitieEgal = expresie.find('=', i);
		const size_t pozitieVirgula = expresie.find(',', i);
		if ((pozitieVirgula != string::npos && pozitieEgal != string::npos && pozitieVirgula < pozitieEgal)
			|| pozitieEgal == string::npos)
		{
			string numeElement = expresie.substr(i, pozitieVirgula - i);

			if (pozitieVirgula != string::npos)
			{
				setareVector(expresie, expresieDeCitit, numeElement, i, pozitieEgal, true);
			}
			else
			{
				const string eroare = "Eroare la atribuire! Expresia nu contine '='!";
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return;
			}
		}
		else
		{
			string numeElement = expresie.substr(i, pozitieVirgula - i);
			bool isVector = false;

			const size_t pozitieParanteza = numeElement.find('[');
			if (pozitieParanteza != string::npos)
			{
				isVector = true;
			}

			if (isVector)
			{
				setareVector(expresie, expresieDeCitit, numeElement, i, pozitieEgal, false);
			}
			else
			{
				string numeElement = expresie.substr(i, pozitieEgal - i);
				seteazaVariabila(expresie, expresieDeCitit, numeElement, i, pozitieEgal);
			}
		}
	}
	// Sterge ultima virgula daca e in plus
	if (expresie.back() == ',')
	{
		expresie.pop_back();
		N->date.expresie = expresie;
	}
	//cout << vectori["test"][0] << " " << vectori["var"][0] << endl;
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
	listaConsola.push_back("Introduceti valoarea pentru variabila " + numeVariabila + ": ");
}

void stopCitirePtParcurgere()
{
	seCiteste = false;
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
	string output, numeVariabilaAfisare;

	bool ghilimele = false;
	for (size_t i = 0; i < expresie.size(); i++)
	{
		char ch = expresie[i];
		string opL = expresie.substr(i, 2);
		if (!ghilimele && esteOperatorLung(opL))
		{
			numeVariabilaAfisare += opL;
			i += 1;
		}
		else if ((!ghilimele && (isalnum(ch) || ch == ' ' || ch == ')' || ch == '(' || esteOperator(ch) || ch == '[' || ch == ']'))
			|| (ghilimele && (ch > 31 && ch < 127 && ch != 34)))
		{
			numeVariabilaAfisare += ch;
		}
		else
		{
			if (!ghilimele)
			{
				if (!numeVariabilaAfisare.empty())
				{
					if (esteVector(numeVariabilaAfisare)) // Check if the variable is a vector
					{
						size_t pozitieParanteza = numeVariabilaAfisare.find('[');
						if (pozitieParanteza != string::npos)
						{
							string numeVector = numeVariabilaAfisare.substr(0, pozitieParanteza);
							string indexStr = numeVariabilaAfisare.substr(pozitieParanteza + 1, numeVariabilaAfisare.size() - pozitieParanteza - 2);

							const int index = static_cast<int>(evaluareExpresie(indexStr));
							if (isnan(static_cast<long double>(index)))
							{
								const string eroare = "Eroare la atribuire! Index-ul vectorului nu este corect!";
								cout << eroare << '\n';
								listaConsola.push_back(eroare);
								return;
							}

							long double valoare = valoareVector(numeVector, index);
							if (!isnan(valoare)) {
								stringstream stream;
								stream << defaultfloat << setprecision(6) << valoare;
								output += stream.str();
								numeVariabilaAfisare.clear();
							}

						}
					}
					else
					{
						long double rezultat = evaluareExpresie(numeVariabilaAfisare);
						if (!isnan(rezultat))
						{
							stringstream stream;
							stream << defaultfloat << setprecision(6) << rezultat;
							output += stream.str();
							numeVariabilaAfisare.clear();
						}
					}
				}
			}
			else
			{
				output += numeVariabilaAfisare;
				numeVariabilaAfisare.clear();
			}
			if (ch == '"')
			{
				ghilimele = !ghilimele;
			}
		}
	}
	if (!ghilimele)
	{
		if (!numeVariabilaAfisare.empty())
		{
			if (esteVector(numeVariabilaAfisare)) // Check if the variable is a vector
			{
				size_t pozitieParanteza = numeVariabilaAfisare.find('[');
				if (pozitieParanteza != string::npos)
				{
					string numeVector = numeVariabilaAfisare.substr(0, pozitieParanteza);
					string indexStr = numeVariabilaAfisare.substr(pozitieParanteza + 1, numeVariabilaAfisare.size() - pozitieParanteza - 2);

					const int index = static_cast<int>(evaluareExpresie(indexStr));
					if (isnan(static_cast<long double>(index)))
					{
						const string eroare = "Eroare la atribuire! Index-ul vectorului nu este corect!";
						cout << eroare << '\n';
						listaConsola.push_back(eroare);
						return;
					}
					long double valoare = valoareVector(numeVector, index);
					stringstream stream;
					stream << defaultfloat << setprecision(6) << valoare;
					output += stream.str();
					numeVariabilaAfisare.clear();

				}
			}
			else
			{
				long double rezultat = evaluareExpresie(numeVariabilaAfisare);
				if (!isnan(rezultat))
				{
					stringstream stream;
					stream << defaultfloat << setprecision(6) << rezultat;
					output += stream.str();
					numeVariabilaAfisare.clear();
				}
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
	return static_cast<bool>(rezultat);
}
