#include "logicaSimboluri.h"
#include "desenareLinie.h"
#include "dimensiuniSimboluri.h"
#include "structs.h"

void logicaCreareSimbol(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const int tip)
{
	//creaza un nod nou si il adauga in lista de arbori
	const Vector2f dimensiune = dimensiuneSimbol(desktop, tip);
	const Vector2f pozitieMouse = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie));
	DateNod date = schimbareDate(static_cast<TipNod>(tip), "", pozitieMouse.x, pozitieMouse.y, dimensiune.x, dimensiune.y);
	if (date.tip == TipNod::START)
		date.expresie = "START";
	else if (date.tip == TipNod::STOP)
		date.expresie = "STOP";

	cout << "Creat: tip= " << static_cast<int>(date.tip) << ", (" << date.x << ',' << date.y << ")\n";
	Arbore ArboreNou;
	atribuireArbore(ArboreNou, date);
	listaArbori.push_back(ArboreNou);
	adaugaSimbolCaObstacole(ArboreNou.radacina);
}

void logicaStergereSimbol(const RenderWindow& fereastraAplicatie)
{
	// Parcurgerea listei de arbori si a fiecarui Arbore pentru a gasi nodul si a-l sterge daca este gasit
	for (auto& A : listaArbori)
	{
		Nod* nodDeSters = gasesteNodCuPozMouse(fereastraAplicatie, A);

		if (nodDeSters != nullptr)
		{
			cout << "Sters: tip= " << static_cast<int>(nodDeSters->date.tip) << ", (" << nodDeSters->date.x << ',' << nodDeSters->date.y << ")\n";
			stergereNod(nodDeSters);
			stergereLiniiObstacoleCuNodulDat(nodDeSters);
			stergeSimbolObstacol(nodDeSters);
			return;
		}
	}
}

Nod* nod1 = nullptr;
Nod* nod2 = nullptr;
void logicaGasireNoduriDeLegat(const RenderWindow& fereastraAplicatie)
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
}

void logicaLegaturaIntreSimboluri()
{
	if (nod1 == nod2 || nod1 == nullptr || nod2 == nullptr)
	{
		nod1 = nullptr;
		nod2 = nullptr;
		return;
	}
	if (esteLegaturaValida(nod1, nod2)) {
		if (nod2->date.tip == TipNod::WHILE) {
			adaugaLinieObstacol(nod1, nod2, true);
		}
		else {
			adaugaLinieObstacol(nod1, nod2, false);
		}
		cout << "Legatura: tip= " << static_cast<int>(nod1->date.tip) << "->" << static_cast<int>(nod2->date.tip) << ", (" << nod1->date.x << ',' <<
			nod1->date.y << ")->(" << nod2->date.x << ',' << nod2->date.y << ")\n";
	}
	nod1 = nullptr;
	nod2 = nullptr;
}