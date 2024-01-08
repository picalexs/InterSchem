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
			if (nodDeSters->st != nullptr && nodDeSters->st->date.tip == TipNod::WHILE
				&& esteNodInArbore(nodDeSters, nodDeSters->st))
				nodDeSters->st->date.tip = TipNod::DACA;
			if (nodDeSters->dr != nullptr && nodDeSters->dr->date.tip == TipNod::WHILE
				&& esteNodInArbore(nodDeSters, nodDeSters->dr))
				nodDeSters->dr->date.tip = TipNod::DACA;
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

bool esteLegaturaValida(Nod*& nodStart, Nod*& nodStop) {
	if (nodStart == nullptr || nodStop == nullptr)
		return false;
	//de la nodul stop nu se poate face legatura
	if (nodStart->date.tip == TipNod::STOP)
		return false;

	//simbolul are deja nr. maxim de fii posibil
	if (((nodStart->date.tip == TipNod::DACA || nodStart->date.tip == TipNod::WHILE) && nodStart->st != nullptr && nodStart->dr != nullptr)
		|| (nodStart->date.tip != TipNod::DACA && nodStart->date.tip != TipNod::WHILE && (nodStart->st != nullptr || nodStart->dr != nullptr)))
		return false;

	//exista deja o legatura intre nodStart si nodStop
	if (existaLinie(nodStart, nodStop)
		&& nodStart->date.tip != TipNod::DACA && nodStop->date.tip != TipNod::DACA
		&& nodStart->date.tip != TipNod::WHILE && nodStop->date.tip != TipNod::WHILE)
		return false;

	const int pozArbore1 = pozitiaArboreleNodului(nodStart);
	const int pozArbore2 = pozitiaArboreleNodului(nodStop);

	if (pozArbore1 == -1 || pozArbore2 == -1)
		return false;

	if (pozArbore1 == pozArbore2)
	{
		if (nodStop->date.tip == TipNod::WHILE)
			return false;
		if (nodStop->date.tip == TipNod::DACA) {
			if (!esteNodInArbore(nodStart, nodStop->st) && !esteNodInArbore(nodStart, nodStop->dr))
				return false;//nu se poate face legatura intre nodStart si nodStop
		}
		else {
			return false; // incerc sa conectez nodStart de nodStop(care nu este while, deci nu este bine)
		}
		if (nodStart->date.tip == TipNod::DACA)
			nodStart->date.tip = TipNod::WHILE;
		else if (nodStop->date.tip == TipNod::DACA)
			nodStop->date.tip = TipNod::WHILE;
	}

	//realizeaza legatura intre nodStart si nodStop
	if (nodStart->st == nullptr) {
		nodStart->st = nodStop;
	}
	else {
		nodStart->dr = nodStop;
	}
	if (pozArbore1 != pozArbore2)
	{
		listaArbori[pozArbore1].nrNoduri = numarNoduriDinArbore(listaArbori[pozArbore1]);
		stergereDinListaArbori(nodStop);
	}
	return true;
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
		if (nod2->date.tip == TipNod::WHILE && esteNodInArbore(nod1, nod2)) {
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

void adaugaLinie(Nod*& nodStart, Nod*& nodStop)
{
	nod1 = nodStart;
	nod2 = nodStop;
	logicaLegaturaIntreSimboluri();
}