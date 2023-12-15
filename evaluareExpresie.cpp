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
	VARIABILA,
	NECUNOSCUT
};

struct atom
{
	TipAtom tip;
	string val;
};

bool esteExpresieCorecta(const vector<atom>&atomi) {
	int parantezeDeschise = 0;
	bool esteCazRau = false;

	for (size_t i = 0; i < atomi.size(); ++i) {
		switch (atomi[i].tip) {
		case TipAtom::PARANTEZA:
			if (atomi[i].val == "(") {
				if (atomi.size() > i + 1 && atomi[i + 1].val == ")") {
					cout << "Eroare: Paranteze deschisa fix langa paranteza inchisa!" << i << endl;
					return false;
				}

				parantezeDeschise++;
			}
			else if (atomi[i].val == ")") {
				if (atomi.size() > i + 1 && atomi[i + 1].val == "(") {
					cout << "Eroare: Paranteze deschisa fix langa paranteza inchisa!" << i << endl;
					return false;
				}
				parantezeDeschise--;
				if (parantezeDeschise < 0) {
					cout << "Eroare: Paranteze inchise in exces la pozitia " << i << endl;
					return false;
				}
			}
			break;
		case TipAtom::FUNCTIE:
			// Verificam daca functia are paranteze deschise dupa ea
			if (i + 1 >= atomi.size() || atomi[i + 1].val != "(") {
				cout << "Eroare: Functia " << atomi[i].val << " trebuie sa fie urmata de o paranteza deschisa la pozitia " << i << endl;
				return false;
			}
			break;
		case TipAtom::OPERATOR:
			// Verificam daca operatorul este intre doi atomi corespunzatori
			if ((i == 0 && atomi[i].val!="-" && atomi[i].val!="+") || i == atomi.size() - 1)
				esteCazRau = true;
			else if (i>0 && atomi[i - 1].val == "(" && ((atomi[i].val != "+" && atomi[i].val != "-") || atomi[i + 1].val == ")"))
				esteCazRau = true;
			else if (i>0 && atomi[i - 1].tip != TipAtom::NUMAR && atomi[i - 1].tip != TipAtom::VARIABILA && atomi[i - 1].tip != TipAtom::FUNCTIE && atomi[i - 1].tip!=TipAtom::PARANTEZA)
				esteCazRau = true;
			else if (atomi.size() > i + 1 && atomi[i + 1].tip != TipAtom::NUMAR && atomi[i + 1].tip != TipAtom::VARIABILA && atomi[i + 1].tip != TipAtom::FUNCTIE && atomi[i + 1].val != "(")
				esteCazRau = true;
			else if (atomi.size() > i + 1 && atomi[i + 1].val == ")" && ((atomi[i].val != "+" && atomi[i].val != "-") || atomi[i - 1].val == "("))
				esteCazRau = true;

			if(esteCazRau)
			{
				cout << "Eroare: Operatorul " << atomi[i].val << " trebuie sa fie intre doi atomi la pozitia " << i << endl;
				return false;
			}
			break;
		case TipAtom::VARIABILA:
			// Verificam daca dupa o variabila apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")") {
				cout << "Eroare: Variabila " << atomi[i].val << " trebuie sa fie urmata de un operator la pozitia " << i << endl;
				return false;
			}
			break;
		case TipAtom::NUMAR:
			// Verificam daca dupa un numar apare altceva decat un operator sau o paranteza
			if (i + 1 < atomi.size() && atomi[i + 1].tip != TipAtom::OPERATOR && atomi[i + 1].val != ")") {
				cout << "Eroare: Numarul " << atomi[i].val << " trebuie sa fie urmat de un operator la pozitia " << i << endl;
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

	if (parantezeDeschise != 0) {
		cout << "Eroare: Paranteze deschise fara inchidere" << endl;
		return false;
	}

	return true;
}

vector<atom> atomizare(const string& expresie)
{
	vector<atom> atomi;
	string atomCurent;

	for (char ch : expresie)
	{
		if (!isspace(ch))
		{
			if (esteCifra(ch) || ch == '.')
			{
				atomCurent += ch;//daca e nr concatenam cifrele
			}
			else
			{
				if (esteNumar(atomCurent))
				{
					atomi.push_back({ TipAtom::NUMAR, atomCurent });
					atomCurent.clear();
				}
				else if (esteFunctie(atomCurent))//FUNCTIE
				{
					atomi.push_back({ TipAtom::FUNCTIE, atomCurent });
					atomCurent.clear();
				}
				else if (esteVariabila(atomCurent))//VARIABILA
				{
					atomi.push_back({ TipAtom::VARIABILA, atomCurent });
					atomCurent.clear();
				}
				if (esteOperator(ch))//OPERATOR
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({ TipAtom::NUMAR, atomCurent });
						atomCurent.clear();
					}
					atomi.push_back({ TipAtom::OPERATOR, string(1, ch) });
				}
				else if (ch == '(' || ch == ')')//PARANTEZA
				{
					if (!atomCurent.empty())
					{
						atomi.push_back({ TipAtom::NUMAR, atomCurent });
						atomCurent.clear();
					}
					atomi.push_back({ TipAtom::PARANTEZA, string(1, ch) });
				}
				else//SI...(N), Varia...(bila), C..(os), -...(1)
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


void evaluareExpresie()
{
	//cream variabile pentru testare.
	seteazaVariabila("x1", 7.0);
	seteazaVariabila("zero", 0);
	seteazaVariabila("val", 15);

	
	string expresie;
	//expresie ="-sin(-sin(-cos(-x1)))+ln(-2/2.3)-2+2/2*3.2/2+cos(-zero*(tg(1)+ctg(1)))";

	do{
		getline(cin, expresie);
		vector<atom> atomi = atomizare(expresie);
		for (const auto& token : atomi)
		{
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
			case TipAtom::NECUNOSCUT:
				cout << "necunoscut";
				break;
			}
			cout << ": " << token.val << endl;
		}
		if (!esteExpresieCorecta(atomi)) {
			//return;
		}
		else {
			cout << "Expresia este buna!" << endl;
		}
	}while (expresie != "stop");

	
}
