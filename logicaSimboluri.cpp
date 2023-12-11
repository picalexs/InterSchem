#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "verificareZonaSimbol.h"

map<Keyboard::Key, bool> esteTastaApasata;

void logicaCreareSimbol(const RenderWindow& window)
{
	for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(key)))
		{
			if (!esteTastaApasata[static_cast<Keyboard::Key>(key)])
			{
				const Vector2i pozitieMouse = Mouse::getPosition(window);
				dateNod date = schimbareDate(key - Keyboard::Num1, "expresie de test", pozitieMouse.x, pozitieMouse.y);
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
				cout << "Sters: tip= " << nodDeSters->date.tip << ", (" << nodDeSters->date.x << ',' << nodDeSters->date.y << ")" << endl;
				stergereLinie(nodDeSters);
				stergereNodFaraSubarbore(A, nodDeSters);
				return;
			}
		}
	}
}

nod* nod1 = nullptr;
nod* nod2 = nullptr;

void logicaLegaturaIntreSimboluri(RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
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
		return;
	if (creareLegatura(nod1, nod2))
		cout << "Legatura: tip= " << nod1->date.tip << "->" << nod2->date.tip << ", (" << nod1->date.x << ',' <<
		nod1->date.y << ")->(" << nod2->date.x << ',' << nod2->date.y << ")" << endl;
	nod1 = nullptr;
	nod2 = nullptr;
}
