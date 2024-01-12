#include "functiiMatematice.h"
#include "evaluareExpresie.h"
#include "functiiNod.h"
#include "structs.h"
#include "functiiExpresie.h"

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
	if (atomi.empty())
		return false;
	for (size_t i = 0; i < atomi.size(); ++i)
	{
		switch (atomi[i].tip)
		{
		case TipAtom::PARANTEZA:
			if (atomi[i].val == "(")
			{
				if (atomi.size() > i + 1 && atomi[i + 1].val == ")")
				{
					const string eroare = "Eroare: Paranteze deschisa fix langa paranteza inchisa!" + to_string(i);
					cout << eroare << '\n';
					listaConsola.push_back(eroare);
					return false;
				}

				parantezeDeschise++;
			}
			else if (atomi[i].val == ")")
			{
				if (atomi.size() > i + 1 && atomi[i + 1].val == "(")
				{
					const string eroare = "Eroare: Paranteze deschisa fix langa paranteza inchisa!" + to_string(i);
					cout << eroare << '\n';
					listaConsola.push_back(eroare);
					return false;
				}
				parantezeDeschise--;
				if (parantezeDeschise < 0)
				{
					const string eroare = "Eroare: Paranteze inchise in exces la pozitia " + to_string(i);
					cout << eroare << '\n';
					listaConsola.push_back(eroare);
					return false;
				}
			}
			break;
		case TipAtom::FUNCTIE:
			// Verificam daca functia are paranteze deschise dupa ea
			if (i + 1 >= atomi.size() || atomi[i + 1].val != "(")
			{
				const string eroare = "Eroare: Functia " + atomi[i].val +
					" trebuie sa fie urmata de o paranteza deschisa la pozitia " + to_string(i);
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
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
				const string eroare = "Eroare: Operatorul " + atomi[i].val + " trebuie sa fie intre doi atomi la pozitia " +
					to_string(i);
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return false;
			}
			break;
		case TipAtom::VARIABILA:
			// Verificam daca dupa o variabila apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")")
			{
				const string eroare = "Eroare: Variabila " + atomi[i].val +
					" trebuie sa fie urmata de un operator la pozitia " + to_string(i);
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return false;
			}
			break;
		case TipAtom::NUMAR:
			// Verificam daca dupa un numar apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")")
			{
				const string eroare = atomi[i].val + " trebuie sa fie urmat de un operator la pozitia " + to_string(i);
				cout << eroare << '\n';
				listaConsola.push_back(eroare);
				return false;
			}
			break;
		case TipAtom::NECUNOSCUT:
		{
			const string eroare = "Eroare: Atom necunoscut " + atomi[i].val + " la pozitia " + to_string(i);
			cout << eroare << '\n';
			listaConsola.push_back(eroare);
			return false;
		}
		default:
			break;
		}
	}

	if (parantezeDeschise != 0)
	{
		const string eroare = "Eroare: Paranteze deschise fara inchidere";
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
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
						atomi.push_back({ TipAtom::NECUNOSCUT, atomCurent });
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
	{"&&", {0, false}},
	{"||", {0, false}},
	{"==", {1, false}},
	{"!=", {1, false}},
	{"<", {1, false}},
	{">", {1, false}},
	{"<=", {1, false}},
	{">=", {1, false}},
	{"(", {2, false}},
	{"+", {3, false}},
	{"-", {3, false}},
	{"*", {4, false}},
	{"/", {4, false}},
	{"%", {4, false}},
	{"^", {5, true}},
	{"sin", {6, false}},
	{"cos", {6, false}},
	{"tg", {6, false}},
	{"ctg", {6, false}},
	{"ln", {6, false}},
	{"abs", {6, false}},
	{"sqrt", {6, false}}
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
			const atom& op1 = at;
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
		default:;
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
			stiva.push(valoareVariabila(at.val));
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
				stiva.push(op2); //daca e +, atunci nu se schimba nimic
				continue;
			}

			const long double op1 = stiva.top();
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
				stiva.push(static_cast<long long>(op1) % static_cast<long long>(op2));
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
				stiva.push(static_cast<bool>(op1) && static_cast<bool>(op2));
			}
			else if (at.val == "||")
			{
				stiva.push(static_cast<bool>(op1) || static_cast<bool>(op2));
			}
		}
		else if (at.tip == TipAtom::FUNCTIE)
		{
			const long double op = stiva.top();
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
					const string eroare = "Eroare: Logaritm din numar negativ!";
					cout << eroare << '\n';
					listaConsola.push_back(eroare);
					return 0;
				}
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
					const string eroare = "Eroare: Radical din numar negativ!";
					cout << eroare << '\n';
					listaConsola.push_back(eroare);
					return 0;
				}
			}
		}
	}
	long double rezultat = stiva.top();
	if (abs(rezultat) < 1e-10)
	{
		rezultat = 0; // Daca e foarte aproape de 0 il facem 0.
	}
	return rezultat;
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
		cout << ": " << at.val << '\n';
	}
}

void testareEvaluator()
{
	//variabile pentru testare.
	seteazaVariabila("x1", 7.0);
	seteazaVariabila("zero", 0);
	seteazaVariabila("val", 15);
	atribuireConstanteCunoscute(); //PI,g,e,phi

	//expresie ="-sin(-sin(-cos(-x1)))+ln(abs(-2/2.3))-2+2/2*3.2/2+cos(-zero*(tg(1)+ctg(2)))";
	string expresie;
	do
	{
		cout << "Introduceti expresia: " << '\n';
		getline(cin, expresie);
		stergereSpatii(expresie);
		cout << expresie << '\n';
		vector<atom> atomi = atomizare(expresie);

		if (!esteExpresieCorecta(atomi))
		{
			cout << "Expresie incorecta!" << '\n';
			continue;
		}

		cout << '\n' << "Expresia in forma infixata atomizata: " << '\n';
		afisareAtomi(atomi);
		cout << '\n';

		cout << "Expresia in forma postfixata atomizata: " << '\n';
		vector<atom> atomiPostfixat = conversieInPostfixat(atomi);
		afisareAtomi(atomiPostfixat);
		cout << '\n';

		const long double rezultat = calculeazaExpresiePostfixata(atomiPostfixat);
		cout << "Rezultatul expresiei: " << fixed << setprecision(8) << rezultat << endl;
		cout << '\n';
	} while (expresie != "stop");
}

long double evaluareExpresie(string& expresie)
{
	stergereSpatii(expresie);
	const vector<atom> atomi = atomizare(expresie);
	if (!esteExpresieCorecta(atomi))
	{
		const string eroare = "Eroare: Expresie incorecta: " + expresie;
		cout << eroare << '\n';
		listaConsola.push_back(eroare);
		return NAN;
	}
	const vector<atom> atomiPostfixat = conversieInPostfixat(atomi);
	return calculeazaExpresiePostfixata(atomiPostfixat);
}
