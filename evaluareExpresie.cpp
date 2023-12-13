#include "functiiMatematice.h"
#include "evaluareExpresie.h"
#include "functiiNod.h"
#include <iostream>
#include <vector>
#include <string>

enum class TipAtom
{
	NUMAR,
	OPERATOR,
	FUNCTIE,
	PARANTEZA,
	VARIABILA
};

struct atom
{
	TipAtom tip;
	string val;
};

vector<atom> atomizare(const string& expresie)
{
	vector<atom> atoms;
	string atomCurent;

	for (char ch : expresie)
	{
		if (!isspace(ch))
		{
			if (isdigit(ch) || ch == '.')
			{
				atomCurent += ch;
			}
			else
			{
				if (!atomCurent.empty() && esteFunctie(atomCurent))
				{
					atoms.push_back({TipAtom::FUNCTIE, atomCurent});
					atomCurent.clear();
				}
				else if (!atomCurent.empty() && variabile.find(atomCurent) != variabile.end())
				{
					atoms.push_back({TipAtom::VARIABILA, atomCurent});
					atomCurent.clear();
				}
				if (esteOperator(ch))
				{
					if (!atomCurent.empty())
					{
						atoms.push_back({TipAtom::NUMAR, atomCurent});
						atomCurent.clear();
					}
					atoms.push_back({TipAtom::OPERATOR, string(1, ch)});
				}
				else if (ch == '(' || ch == ')')
				{
					if (!atomCurent.empty())
					{
						atoms.push_back({TipAtom::NUMAR, atomCurent});
						atomCurent.clear();
					}
					atoms.push_back({TipAtom::PARANTEZA, string(1, ch)});
				}
				else
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
					atoms.push_back({TipAtom::FUNCTIE, atomCurent});
				}
				else if (variabile.find(atomCurent) != variabile.end())
				{
					atoms.push_back({TipAtom::VARIABILA, atomCurent});
				}
				else
				{
					atoms.push_back({TipAtom::NUMAR, atomCurent});
				}
				atomCurent.clear();
			}
		}
	}

	if (!atomCurent.empty())
	{
		if (esteFunctie(atomCurent))
		{
			atoms.push_back({TipAtom::FUNCTIE, atomCurent});
		}
		else if (variabile.find(atomCurent) != variabile.end())
		{
			atoms.push_back({TipAtom::VARIABILA, atomCurent});
		}
		else
		{
			atoms.push_back({TipAtom::NUMAR, atomCurent});
		}
	}
	return atoms;
}


void evaluareExpresie()
{
	//cream variabile pentru testare.
	seteazaVariabila("x1", 7.0);
	seteazaVariabila("zero", 0);
	seteazaVariabila("val", 15);

	string expresie = "3.14+sin(x1)*2-ln(2^3)+tg(cos(sin(7.162)))/2/cos(zero)-val/x1";
	vector<atom> atom = atomizare(expresie);

	for (const auto& token : atom)
	{
		cout << "tip ";
		switch (token.tip)
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
		}
		cout << ": " << token.val << endl;
	}
}
