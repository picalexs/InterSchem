#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "evaluareExpresie.h"
#include "functiiMatematice.h"

map<Keyboard::Key, bool> esteTastaApasata;

void logicaCreareSimbol(const RenderWindow& window)
{
	if (!Keyboard::isKeyPressed(Keyboard::LControl))
		return;
	for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(key)))
		{
			if (!esteTastaApasata[static_cast<Keyboard::Key>(key)])
			{
				const Vector2i pozitieMouse = Mouse::getPosition(window);
				dateNod date = schimbareDate(key - Keyboard::Num1, "", pozitieMouse.x, pozitieMouse.y);
				cout << "Creat: tip= " << date.tip << ", (" << date.x << ',' << date.y << ")" << endl;

				arbore ArboreNou;
				atribuireArbore(ArboreNou, date);
				listaArbori.push_back(ArboreNou);

				esteTastaApasata[static_cast<Keyboard::Key>(key)] = true;
			}
		}
		else
		{
			esteTastaApasata[static_cast<Keyboard::Key>(key)] = false;
		}
	}
}

void stergereLinie(const nod* N)
{
	for (auto it = listaLinii.begin(); it != listaLinii.end();)
	{
		if ((it->first.x == N->date.x && it->first.y == N->date.y) ||
			(it->second.x == N->date.x && it->second.x == N->date.y))
		{
			it = listaLinii.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool esteApasatStergere = false;

void logicaStergereSimbol(const RenderWindow& window)
{
	if (!Keyboard::isKeyPressed(Keyboard::Escape) && esteApasatStergere)
	{
		esteApasatStergere = false;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && !esteApasatStergere)
	{
		esteApasatStergere = true;
		// Parcurgerea listei de arbori si a fiecarui arbore pentru a gasi nodul si a-l sterge daca este gasit
		for (auto& A : listaArbori)
		{
			nod* nodDeSters = gasesteNodCuPozMouse(window, A);

			if (nodDeSters != nullptr)
			{
				cout << "Sters: tip= " << nodDeSters->date.tip << ", (" << nodDeSters->date.x << ',' << nodDeSters->date
					.y << ")" << endl;
				stergereLinie(nodDeSters);
				stergereNodFaraSubarbore(A, nodDeSters);
				return;
			}
		}
	}
}

nod* nod1 = nullptr;
nod* nod2 = nullptr;

void logicaLegaturaIntreSimboluri(const RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		if (nod1 == nullptr)
		{
			nod1 = gasesteNodListaCuPozMouse(window);
		}
		nod* nod2Nou = gasesteNodListaCuPozMouse(window);
		if (nod2 == nullptr || nod2 == nod1 || nod2Nou != nod2)
		{
			nod2 = nod2Nou;
		}
		return;
	}
	if (nod1 == nod2 || nod1 == nullptr || nod2 == nullptr)
	{
		nod1 = nullptr;
		nod2 = nullptr;
		return;
	}
	if (creareLegatura(nod1, nod2))
		cout << "Legatura: tip= " << nod1->date.tip << "->" << nod2->date.tip << ", (" << nod1->date.x << ',' <<
		nod1->date.y << ")->(" << nod2->date.x << ',' << nod2->date.y << ")" << endl;
	nod1 = nullptr;
	nod2 = nullptr;
}

void logicaSimboluri(const RenderWindow& window)
{
	logicaCreareSimbol(window);
	logicaStergereSimbol(window);
	logicaLegaturaIntreSimboluri(window);
}

//caute expresii de tipul "var1 = expr1" sau "var1 = expr1, var2 = expr2, ..." si le salveaza in map-ul "variabile"
void logicaAtribuire(nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;
	string expresie = N->date.expresie;
	string numeVariabila, expresieDeCitit;
	int nrVariabile = 0, nrVirgule = 0;

	size_t i = 0;
	while (i < expresie.size())
	{
		const size_t pozitieEgal = expresie.find('=', i);
		if (pozitieEgal == string::npos)
		{
			cout << "Eroare la atribuire! Expresia nu contine '='!" << endl;
			return;
		}
		numeVariabila = expresie.substr(i, pozitieEgal - i);
		for (const char ch : numeVariabila)
			if (!isalnum(ch))
			{
				cout << "Eroare la atribuire! Numele variabilei nu este corect!" << endl;
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
				cout << "Eroare la atribuire! Expresia este goala!" << endl;
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
			cout << "Eroare la atribuire! Expresia este gresita!" << endl;
		}
	}
	//sterge ultima virgula daca e in plus
	if (nrVariabile == nrVirgule)
	{
		for (size_t i = expresie.size() - 1; i >= 0; i--)
			if (expresie[i] == ',')
			{
				expresie.erase(i, 1);
				N->date.expresie = expresie;
				return;
			}
	}
}

void logicaCitire(nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;
	cout << "Introduceti valoarea pentru variabila " << N->date.expresie << ": ";
	getline(cin, N->date.expresie); //temporar
}

void logicaAfisare(nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return;

	string expresie = N->date.expresie;
	expresie[expresie.size()] = '\0';
	string output, numeVariabila;
	size_t i = 0;

	bool ghilimele = false;
	for (int i = 0; i < expresie.size(); i++)
	{
		char ch = expresie[i];
		string opL = expresie.substr(i, 2);
		if ((!ghilimele && (isalnum(ch) || ch == ' ' || ch == ')' || ch == '(' || esteOperator(ch) || esteOperatorLung(opL)))
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
						output += to_string(rezultat);
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
				output += to_string(rezultat);
				numeVariabila.clear();
			}
		}
	}
	cout << output << endl;//trebuie schimbat cu afisare pe ecran
}


bool logicaDaca(nod* N)
{
	if (N == nullptr || N->date.expresie.empty())
		return false;
	long double rezultat = evaluareExpresie(N->date.expresie);
	if (rezultat)
		return false; //stanga este considerat adevarat, dar e notat cu 0/false
	return true;
}
