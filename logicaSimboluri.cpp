#include "logicaSimboluri.h"
#include "dimensiuniSimboluri.h"
#include "structs.h"

map<Keyboard::Key, bool> esteTastaApasata;

void logicaCreareSimbol(const RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	if (!Keyboard::isKeyPressed(Keyboard::LControl))
		return;
	for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(key)))
		{
			if (!esteTastaApasata[static_cast<Keyboard::Key>(key)])
			{
				int tip = key - Keyboard::Num1;
				const Vector2f dimensiuni = dimensiuniSimbol(desktop, tip);
				const Vector2f pozitieMouse = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie));
				DateNod date = schimbareDate(tip, "", pozitieMouse.x, pozitieMouse.y, dimensiuni.x, dimensiuni.y);
				if (date.tip == 0)
					date.expresie = "START";
				else if (date.tip == 1)
					date.expresie = "STOP";
				cout << "Creat: tip= " << date.tip << ", (" << date.x << ',' << date.y << ")" << endl;

				Arbore ArboreNou;
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

void stergereLinie(const Nod* N)
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

void logicaStergereSimbol(const RenderWindow& fereastraAplicatie)
{
	if (!Keyboard::isKeyPressed(Keyboard::Escape) && esteApasatStergere)
	{
		esteApasatStergere = false;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && !esteApasatStergere)
	{
		esteApasatStergere = true;
		// Parcurgerea listei de arbori si a fiecarui Arbore pentru a gasi nodul si a-l sterge daca este gasit
		for (auto& A : listaArbori)
		{
			Nod* nodDeSters = gasesteNodCuPozMouse(fereastraAplicatie, A);

			if (nodDeSters != nullptr)
			{
				cout << "Sters: tip= " << nodDeSters->date.tip << ", (" << nodDeSters->date.x << ',' << nodDeSters->date.y << ")\n";
				stergereLinie(nodDeSters);
				stergereNod(nodDeSters);
				return;
			}
		}
	}
}

Nod* nod1 = nullptr;
Nod* nod2 = nullptr;

void logicaLegaturaIntreSimboluri(const RenderWindow& fereastraAplicatie)
{
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		if (nod1 == nullptr)
		{
			nod1 = gasesteNodListaCuPozMouse(fereastraAplicatie);
		}
		Nod* nod2Nou = gasesteNodListaCuPozMouse(fereastraAplicatie);
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
		nod1->date.y << ")->(" << nod2->date.x << ',' << nod2->date.y << ")\n";
	nod1 = nullptr;
	nod2 = nullptr;
}

void logicaSimboluri(const RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	logicaCreareSimbol(fereastraAplicatie, desktop);
	logicaStergereSimbol(fereastraAplicatie);
	logicaLegaturaIntreSimboluri(fereastraAplicatie);
}
