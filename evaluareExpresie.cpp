#include "functiiMatematice.h"
#include "evaluareExpresie.h"
#include "functiiNod.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
using namespace std;

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

	for (int i = 0; i < atomi.size(); ++i)
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
			{
				esteCazRau = true;
				//daca avem un op. pe prima pozitie si nu e unar sau avem unul pe ultima pozitie, atunci nu e bine
			}
			else if (i > 0 && atomi[i - 1].val == "("
				&& ((atomi[i].val != "+" && atomi[i].val != "-") || atomi[i + 1].val == ")"))
			{
				esteCazRau = true;
				//daca avem un op. dupa '(' si e diferit de +,- sau urmeaza o paranteza inchisa dupa op., atunci nu e bine
			}
			else if (i > 0 && atomi[i - 1].tip != TipAtom::NUMAR && atomi[i - 1].tip != TipAtom::VARIABILA
				&& atomi[i - 1].tip != TipAtom::FUNCTIE && atomi[i - 1].tip != TipAtom::PARANTEZA)
			{
				esteCazRau = true;
				//daca nu avem un nr,var,fct sau '(' inainte de op., atunci nu e bine
			}
			else if (atomi.size() > i + 1 && atomi[i + 1].tip != TipAtom::NUMAR && atomi[i + 1].tip !=
				TipAtom::VARIABILA
				&& atomi[i + 1].tip != TipAtom::FUNCTIE && atomi[i + 1].val != "(")
			{
				esteCazRau = true;
				//daca nu avem un nr, var, fct sau '(' dupa op., atunci nu e bine
			}
			else if (atomi.size() > i + 1 && atomi[i + 1].val == ")" && (atomi[i - 1].val == "("))
			{
				esteCazRau = true;
				//daca avem (op) nu este bine
			}
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
				if (esteNumar(atomCurent)) //NUMAR
				{
					atomi.push_back({ TipAtom::NUMAR, atomCurent });
					atomCurent.clear();
				}
				else if (esteFunctie(atomCurent)) //FUNCTIE
				{
					atomi.push_back({ TipAtom::FUNCTIE, atomCurent });
					atomCurent.clear();
				}
				else if (esteVariabila(atomCurent)) //VARIABILA
				{
					atomi.push_back({ TipAtom::VARIABILA, atomCurent });
					atomCurent.clear();
				}

				string op = expresie.substr(i, 2);
				if (esteOperator(ch) && !esteOperatorLung(op)) //OPERATOR
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({ TipAtom::NUMAR, atomCurent });
						atomCurent.clear();
					}
					atomi.push_back({ TipAtom::OPERATOR, string(1, ch) });
				}
				else if (esteOperatorLung(op)) //OPERATOR LUNG
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({ TipAtom::NUMAR, atomCurent });
						atomCurent.clear();
					}
					atomi.push_back({ TipAtom::OPERATOR, op });
					i++;
				}
				else if (ch == '(' || ch == ')') //PARANTEZA
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({ TipAtom::NUMAR, atomCurent });
						atomCurent.clear();
					}
					atomi.push_back({ TipAtom::PARANTEZA, string(1, ch) });
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
					atomi.push_back({ TipAtom::FUNCTIE, atomCurent });
				}
				else if (esteVariabila(atomCurent))
				{
					atomi.push_back({ TipAtom::VARIABILA, atomCurent });
				}
				else if (atomCurent.size() == 1 && esteOperator(atomCurent[0]))
				{
					atomi.push_back({ TipAtom::OPERATOR, atomCurent });
				}
				else if (atomCurent.size() == 2 && esteOperatorLung(atomCurent))
				{
					atomi.push_back({ TipAtom::OPERATOR, atomCurent });
				}
				else if (esteNumar(atomCurent))
				{
					atomi.push_back({ TipAtom::NUMAR, atomCurent });
				}
				else
				{
					atomi.push_back({ TipAtom::NECUNOSCUT, atomCurent });
				}
			}
		}
	}

	if (!atomCurent.empty())
	{
		if (esteFunctie(atomCurent))
		{
			atomi.push_back({ TipAtom::FUNCTIE, atomCurent });
		}
		else if (esteVariabila(atomCurent))
		{
			atomi.push_back({ TipAtom::VARIABILA, atomCurent });
		}
		else if (atomCurent.size() == 1 && esteOperator(atomCurent[0]))
		{
			atomi.push_back({ TipAtom::OPERATOR, atomCurent });
		}
		else if (atomCurent.size() == 2 && esteOperatorLung(atomCurent))
		{
			atomi.push_back({ TipAtom::OPERATOR, atomCurent });
		}
		else if (esteNumar(atomCurent))
		{
			atomi.push_back({ TipAtom::NUMAR, atomCurent });
		}
		else
		{
			atomi.push_back({ TipAtom::NECUNOSCUT, atomCurent });
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
	{"-", {2, false}},
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

vector<atom> conversieInPostfixat(const vector<atom>& atomi)
{
	//algoritm de conversie a expresiei din forma infixata in forma postfixata
	vector<atom> atomiPostfixat;
	stack<atom> coada;

	for (const auto& at : atomi)
	{
		switch (at.tip)
		{
		case TipAtom::NUMAR:
		case TipAtom::VARIABILA:
		{
			atomiPostfixat.push_back(at);
			break;
		}
		case TipAtom::OPERATOR:
		case TipAtom::FUNCTIE:
		{
			atom op1 = at;
			while (!coada.empty())
			{
				atom op2 = coada.top();
				if ((!reguliOperatori[op1.val].asociativDreapta
					&& reguliOperatori[op1.val].precedenta <= reguliOperatori[op2.val].precedenta)
					|| (reguliOperatori[op1.val].asociativDreapta
						&& reguliOperatori[op1.val].precedenta < reguliOperatori[op2.val].precedenta))
				{
					atomiPostfixat.push_back(coada.top());
					coada.pop();
					continue;
				}
				break;
			}
			coada.push(at);
		}
		break;
		case TipAtom::PARANTEZA:
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
			break;
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
			stiva.push(stold(at.val)); //stold converteste stringul in long double
		}
		else if (at.tip == TipAtom::VARIABILA)
		{
			stiva.push(obtineValoareVariabilaDupaNume(at.val));
		}
		else if (at.tip == TipAtom::OPERATOR)
		{
			long double op2 = stiva.top();
			stiva.pop();
			if (stiva.empty())
			{
				if (at.val == "-")
				{
					stiva.push(-op2); //daca e -, atunci se schimba semnul
					continue;
				}
				else
				{
					stiva.push(op2); //daca e +, atunci nu se schimba nimic
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
				if (op < 0)
				{
					cout << "Eroare: Logaritm din numar negativ!" << endl;
					return 0;
				}
				else
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
				else
				{
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

void stergereSpatii(string& expresie)
{
	for (int i = 0; i < expresie.size();)
	{
		if (esteSpatiu(expresie[i]))
			expresie.erase(i, 1);
		else
			i++;
	}
}

void testareEvaluator()
{
	//cream variabile pentru testare.
	seteazaVariabila("x1", 7.0);
	seteazaVariabila("zero", 0);
	seteazaVariabila("val", 15);

	//expresie ="-sin(-sin(-cos(-x1)))+ln(abs(-2/2.3))-2+2/2*3.2/2+cos(-zero*(tg(1)+ctg(2)))";
	string expresie;
	do
	{
		cout << "Introduceti expresia: " << endl;
		getline(cin, expresie);
		stergereSpatii(expresie);
		cout << expresie << endl;
		vector<atom> atomi = atomizare(expresie);

		if (!esteExpresieCorecta(atomi))
		{
			cout << "Expresie incorecta!" << endl;
			continue;
		}

		cout << endl << "Expresia in forma infixata atomizata: " << endl;
		afisareAtomi(atomi);
		cout << endl;

		cout << "Expresia in forma postfixata atomizata: " << endl;
		vector<atom> atomiPostfixat = conversieInPostfixat(atomi);
		afisareAtomi(atomiPostfixat);
		cout << endl;

		cout << "Rezultatul expresiei: " << calculeazaExpresiePostfixata(atomiPostfixat) << endl;
		cout << endl;
	} while (expresie != "stop");
}

long double evaluareExpresie(string& expresie)
{
	stergereSpatii(expresie);
	vector<atom> atomi = atomizare(expresie);
	if (!esteExpresieCorecta(atomi))
	{
		cout << "Expresie incorecta: " << expresie << endl;
		return NAN;
	}
	vector<atom> atomiPostfixat = conversieInPostfixat(atomi);
	return calculeazaExpresiePostfixata(atomiPostfixat);
}

void atribuireConstanteCunoscute()
{
	seteazaVariabila("PI", 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899f);
	seteazaVariabila("e", 2.718281828459045235360287471352662497757247093699959574966967627724076630353f);
	seteazaVariabila("g", 9.80665f);
	seteazaVariabila("phi", 1.61803398874989484820458683436563811772030917980576286213544862270526046281890f);
}
