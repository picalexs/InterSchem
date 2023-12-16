#include "functiiMatematice.h"
#include "evaluareExpresie.h"
#include "functiiNod.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

enum class TipAtom
{
	NUMAR,
	OPERATOR,
	FUNCTIE,
	PARANTEZA,
	VARIABILA,
	NECUNOSCUT
};

struct atom
{
	TipAtom tip;
	string val;
};

bool esteExpresieCorecta(const vector<atom>& atomi)
{
	int parantezeDeschise = 0;
	bool esteCazRau = false;

	for (size_t i = 0; i < atomi.size(); ++i)
	{
		switch (atomi[i].tip)
		{
		case TipAtom::PARANTEZA:
			if (atomi[i].val == "(")
			{
				if (atomi.size() > i + 1 && atomi[i + 1].val == ")")
				{
					cout << "Eroare: Paranteze deschisa fix langa paranteza inchisa!" << i << endl;
					return false;
				}

				parantezeDeschise++;
			}
			else if (atomi[i].val == ")")
			{
				if (atomi.size() > i + 1 && atomi[i + 1].val == "(")
				{
					cout << "Eroare: Paranteze deschisa fix langa paranteza inchisa!" << i << endl;
					return false;
				}
				parantezeDeschise--;
				if (parantezeDeschise < 0)
				{
					cout << "Eroare: Paranteze inchise in exces la pozitia " << i << endl;
					return false;
				}
			}
			break;
		case TipAtom::FUNCTIE:
			// Verificam daca functia are paranteze deschise dupa ea
			if (i + 1 >= atomi.size() || atomi[i + 1].val != "(")
			{
				cout << "Eroare: Functia " << atomi[i].val <<
					" trebuie sa fie urmata de o paranteza deschisa la pozitia " << i << endl;
				return false;
			}
			break;
		case TipAtom::OPERATOR:
			// Verificam daca operatorul este intre doi atomi corespunzatori
			if ((i == 0 && atomi[i].val != "-" && atomi[i].val != "+") || i == atomi.size() - 1)
				esteCazRau = true;
			else if (i > 0 && atomi[i - 1].val == "(" && ((atomi[i].val != "+" && atomi[i].val != "-") || atomi[i + 1].
				val == ")"))
				esteCazRau = true;
			else if (i > 0 && atomi[i - 1].tip != TipAtom::NUMAR && atomi[i - 1].tip != TipAtom::VARIABILA && atomi[i -
				1].tip != TipAtom::FUNCTIE && atomi[i - 1].tip != TipAtom::PARANTEZA)
				esteCazRau = true;
			else if (atomi.size() > i + 1 && atomi[i + 1].tip != TipAtom::NUMAR && atomi[i + 1].tip !=
				TipAtom::VARIABILA && atomi[i + 1].tip != TipAtom::FUNCTIE && atomi[i + 1].val != "(")
				esteCazRau = true;
			else if (atomi.size() > i + 1 && atomi[i + 1].val == ")" && ((atomi[i].val != "+" && atomi[i].val != "-") ||
				atomi[i - 1].val == "("))
				esteCazRau = true;

			if (esteCazRau)
			{
				cout << "Eroare: Operatorul " << atomi[i].val << " trebuie sa fie intre doi atomi la pozitia " << i <<
					endl;
				return false;
			}
			break;
		case TipAtom::VARIABILA:
			// Verificam daca dupa o variabila apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")")
			{
				cout << "Eroare: Variabila " << atomi[i].val << " trebuie sa fie urmata de un operator la pozitia " << i
					<< endl;
				return false;
			}
			break;
		case TipAtom::NUMAR:
			// Verificam daca dupa un numar apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")")
			{
				cout << "Eroare: Numarul " << atomi[i].val << " trebuie sa fie urmat de un operator la pozitia " << i <<
					endl;
				return false;
			}
			break;
		case TipAtom::NECUNOSCUT:
			{
				cout << "Eroare: Atom necunoscut " << atomi[i].val << " la pozitia " << i << endl;
				return false;
			}
		default:
			break;
		}
	}

	if (parantezeDeschise != 0)
	{
		cout << "Eroare: Paranteze deschise fara inchidere" << endl;
		return false;
	}

	return true;
}

vector<atom> atomizare(const string& expresie)
{
	vector<atom> atomi;
	string atomCurent;

	for (char i = 0; i < expresie.size(); i++)
	{
		char ch = expresie[i];
		if (!isspace(ch))
		{
			if (esteCifra(ch) || ch == '.')
			{
				atomCurent += ch; //daca e nr concatenam cifrele
			}
			else
			{
				if (esteNumar(atomCurent))
				{
					atomi.push_back({TipAtom::NUMAR, atomCurent});
					atomCurent.clear();
				}
				else if (esteFunctie(atomCurent)) //FUNCTIE
				{
					atomi.push_back({TipAtom::FUNCTIE, atomCurent});
					atomCurent.clear();
				}
				else if (esteVariabila(atomCurent)) //VARIABILA
				{
					atomi.push_back({TipAtom::VARIABILA, atomCurent});
					atomCurent.clear();
				}

				string op = expresie.substr(i, 2);
				if (esteOperator(ch) && !esteOperatorLung(op)) //OPERATOR
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({TipAtom::NUMAR, atomCurent});
						atomCurent.clear();
					}
					atomi.push_back({TipAtom::OPERATOR, string(1, ch)});
				}
				else if (esteOperatorLung(op)) //OPERATOR LUNG
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({TipAtom::NUMAR, atomCurent});
						atomCurent.clear();
					}
					atomi.push_back({TipAtom::OPERATOR, op});
					i++;
				}
				else if (ch == '(' || ch == ')') //PARANTEZA
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({TipAtom::NUMAR, atomCurent});
						atomCurent.clear();
					}
					atomi.push_back({TipAtom::PARANTEZA, string(1, ch)});
				}
				else //SI...(N), Varia...(bila), C..(os), -...(1)
				{
					atomCurent += ch;
				}
			}
		}
		else
		{
			if (!atomCurent.empty())
			{
				if (esteFunctie(atomCurent))
				{
					atomi.push_back({TipAtom::FUNCTIE, atomCurent});
				}
				else if (esteVariabila(atomCurent))
				{
					atomi.push_back({TipAtom::VARIABILA, atomCurent});
				}
				else if (atomCurent.size() == 1 && esteOperator(atomCurent[0]))
				{
					atomi.push_back({TipAtom::OPERATOR, atomCurent});
				}
				else if (atomCurent.size() == 2 && esteOperatorLung(atomCurent))
				{
					atomi.push_back({TipAtom::OPERATOR, atomCurent});
				}
				else if (esteNumar(atomCurent))
				{
					atomi.push_back({TipAtom::NUMAR, atomCurent});
				}
				else
				{
					atomi.push_back({TipAtom::NECUNOSCUT, atomCurent});
				}
			}
		}
	}

	if (!atomCurent.empty())
	{
		if (esteFunctie(atomCurent))
		{
			atomi.push_back({TipAtom::FUNCTIE, atomCurent});
		}
		else if (esteVariabila(atomCurent))
		{
			atomi.push_back({TipAtom::VARIABILA, atomCurent});
		}
		else if (atomCurent.size() == 1 && esteOperator(atomCurent[0]))
		{
			atomi.push_back({TipAtom::OPERATOR, atomCurent});
		}
		else if (atomCurent.size() == 2 && esteOperatorLung(atomCurent))
		{
			atomi.push_back({TipAtom::OPERATOR, atomCurent});
		}
		else if (esteNumar(atomCurent))
		{
			atomi.push_back({TipAtom::NUMAR, atomCurent});
		}
		else
		{
			atomi.push_back({TipAtom::NECUNOSCUT, atomCurent});
		}
	}
	return atomi;
}

struct operatori
{
	int precedenta;
	bool asociativDreapta;
};

map<string, operatori> reguliOperatori = {
	{"==", {0, false}},
	{"!=", {0, false}},
	{"<", {0, false}},
	{">", {0, false}},
	{"<=", {0, false}},
	{">=", {0, false}},
	{"&&", {0, false}},
	{"||", {0, false}},
	{"(", {1, false}},
	{"+", {2, false}},
	{"-", {2, false}}, //!!!de adaugat si pentru unar caz
	{"*", {3, false}},
	{"/", {3, false}},
	{"%", {3, false}},
	{"^", {4, true}},
	{"sin", {5, false}},
	{"cos", {5, false}},
	{"tg", {5, false}},
	{"ctg", {5, false}},
	{"ln", {5, false}},
	{"abs", {5, false}},
	{"sqrt", {5, false}}
};

vector<atom> ShuntingYard(const vector<atom>& atomi)
{
	//algoritm de conversie a expresiei din forma infixata in forma postfixata
	vector<atom> atomiPostfixat;
	stack<atom> coada;

	for (const auto& at : atomi)
	{
		if (at.tip == TipAtom::NUMAR || at.tip == TipAtom::VARIABILA)
		{
			atomiPostfixat.push_back(at);
		}
		else if (at.tip == TipAtom::OPERATOR || at.tip == TipAtom::FUNCTIE)
		{
			atom op1 = at;

			while (!coada.empty())
			{
				atom op2 = coada.top();
				if ((!reguliOperatori[op1.val].asociativDreapta && reguliOperatori[op1.val].precedenta <=
						reguliOperatori[op2.val].precedenta)
					|| (reguliOperatori[op1.val].asociativDreapta && reguliOperatori[op1.val].precedenta <
						reguliOperatori[op2.val].precedenta))
				{
					atomiPostfixat.push_back(coada.top());
					coada.pop();
					continue;
				}
				break;
			}
			coada.push(at);
		}
		else if (at.tip == TipAtom::PARANTEZA)
		{
			if (at.val == "(")
			{
				coada.push(at);
			}
			else if (at.val == ")")
			{
				while (!coada.empty() && coada.top().val != "(")
				{
					atomiPostfixat.push_back(coada.top());
					coada.pop();
				}
				coada.pop(); // Eliminate ( din coada
			}
		}
	}
	while (!coada.empty())
	{
		atomiPostfixat.push_back(coada.top());
		coada.pop();
	}
	return atomiPostfixat;
}

long double calculeazaExpresiePostfixata(const vector<atom>& atomi)
{
	stack<long double> stiva;
	for (const auto& at : atomi)
	{
		if (at.tip == TipAtom::NUMAR)
		{
			stiva.push(stold(at.val));
		}
		else if (at.tip == TipAtom::VARIABILA)
		{
			stiva.push(obtineValoareVariabilaDupaNume(at.val));
		}
		else if (at.tip == TipAtom::OPERATOR)
		{
			long double op2 = stiva.top();
			stiva.pop();
			if (stiva.empty()) {
				if (at.val == "-") {
					stiva.push(-op2);
					continue;
				}
				else {
					stiva.push(op2);
					continue;
				}
			}

			long double op1 = stiva.top();
			stiva.pop();

			if (at.val == "+")
			{
				stiva.push(op1 + op2);
			}
			else if (at.val == "-")
			{
				stiva.push(op1 - op2);
			}
			else if (at.val == "*")
			{
				stiva.push(op1 * op2);
			}
			else if (at.val == "/")
			{
				stiva.push(op1 / op2);
			}
			else if (at.val == "%")
			{
				stiva.push(fmod(op1, op2));
			}
			else if (at.val == "^")
			{
				stiva.push(pow(op1, op2));
			}
			else if (at.val == "==")
			{
				stiva.push(op1 == op2);
			}
			else if (at.val == "!=")
			{
				stiva.push(op1 != op2);
			}
			else if (at.val == "<")
			{
				stiva.push(op1 < op2);
			}
			else if (at.val == ">")
			{
				stiva.push(op1 > op2);
			}
			else if (at.val == "<=")
			{
				stiva.push(op1 <= op2);
			}
			else if (at.val == ">=")
			{
				stiva.push(op1 >= op2);
			}
			else if (at.val == "&&")
			{
				stiva.push(op1 && op2);
			}
			else if (at.val == "||")
			{
				stiva.push(op1 || op2);
			}
		}
		else if (at.tip == TipAtom::FUNCTIE)
		{
			long double op = stiva.top();
			stiva.pop();

			if (at.val == "sin")
			{
				stiva.push(sin(op));
			}
			else if (at.val == "cos")
			{
				stiva.push(cos(op));
			}
			else if (at.val == "tg")
			{
				stiva.push(tan(op));
			}
			else if (at.val == "ctg")
			{
				stiva.push(1 / tan(op));
			}
			else if (at.val == "ln")
			{
				stiva.push(log(op));
			}
			else if (at.val == "abs")
			{
				stiva.push(abs(op));
			}
			else if (at.val == "sqrt")
			{
				if (op >= 0)
					stiva.push(sqrt(op));
				else {
					cout << "Eroare: Radical din numar negativ!" << endl;
					return 0;
				}
			}
		}
	}
	return stiva.top();
}

void afisareAtomi(const vector<atom>& atomi)
{
	for (const auto& at : atomi)
	{
		switch (at.tip)
		{
		case TipAtom::NUMAR:
			cout << "numar";
			break;
		case TipAtom::OPERATOR:
			cout << "operator";
			break;
		case TipAtom::FUNCTIE:
			cout << "functie";
			break;
		case TipAtom::PARANTEZA:
			cout << "paranteza";
			break;
		case TipAtom::VARIABILA:
			cout << "variabila";
			break;
		case TipAtom::NECUNOSCUT:
			cout << "!! necunoscut";
			break;
		}
		cout << ": " << at.val << endl;
	}
}

void evaluareExpresie()
{
	//cream variabile pentru testare.
	seteazaVariabila("x1", 7.0);
	seteazaVariabila("zero", 0);
	seteazaVariabila("val", 15);

	string expresie;
	//expresie ="-sin(-sin(-cos(-x1)))+ln(-2/2.3)-2+2/2*3.2/2+cos(-zero*(tg(1)+ctg(1)))";
	
	do
	{
		cout << "Introduceti expresia: " << endl;
		getline(cin, expresie);
		vector<atom> atomi = atomizare(expresie);
		if (!esteExpresieCorecta(atomi))
		{
			cout << "Expresie incorecta!" << endl;
			continue;
		}
		cout << "Expresia in forma infixata atomizata: " << endl;
		afisareAtomi(atomi);
		cout << endl;
		cout << "Expresia in forma postfixata atomizata: " << endl;
		vector<atom> atomiPostfixat = ShuntingYard(atomi);
		afisareAtomi(atomiPostfixat);
		cout << endl;
		cout<<"Rezultatul expresiei: "<< calculeazaExpresiePostfixata(atomiPostfixat) << endl;
		cout << endl;
	}
	while (expresie != "stop");
}
