#include "desenareLinie.h"
#include <queue>

struct Punct
{
	int x;
	int y;
};

struct Linie
{
	vector<Punct> coordonateSegment;
	Color culoareLinie;
};

void desenareSegmentLinie(int x1, int y1, int x2, int y2, Color culoareLinie)
{
	//deseneaza un segment de linie intre doua puncte
	//x1, y1, x2, y2 sunt coordonatele celor doua puncte
	//culoareLinie este culoarea liniei
	//desenareLinie(x1, y1, x2, y2, culoareLinie);
}

void desenareLinie(const Linie& linie) {
	for (size_t i = 0; i < linie.coordonateSegment.size() - 1; ++i) {
		const auto coordonateCurente = linie.coordonateSegment[i];
		const auto coordonateUrmatoare = linie.coordonateSegment[i + 1];
		const auto culoareLinie = linie.culoareLinie;
		desenareSegmentLinie(coordonateCurente.x, coordonateCurente.y, coordonateUrmatoare.x, coordonateUrmatoare.y, culoareLinie);
	}
}

int interval(int valoare, int min, int max)
{
	if (valoare < min)
		return min;
	if (valoare > max)
		return max;
	return valoare;
}

vector<Punct> gasesteDrumBFS(const vector<vector<bool>>& matriceObstacole, const Punct& start, const Punct& stop, int nrLinii, int nrColoane) {
	vector<vector<bool>> vizitat(nrLinii, vector<bool>(nrColoane, false));
	vector<vector<Punct>> parinte(nrLinii, vector<Punct>(nrColoane, { -1, -1 }));

	queue<Punct> coada;
	coada.push(start);
	vizitat[start.y][start.x] = true;

	vector<int> dirX = { -1, 0, 1, 0 };
	vector<int> dirY = { 0, 1, 0, -1 };

	while (!coada.empty()) {
		Punct current = coada.front();
		coada.pop();

		if (current.x == stop.x && current.y == stop.y) {
			break;
		}

		for (int i = 0; i < 4; ++i) {
			int newX = current.x + dirX[i];
			int newY = current.y + dirY[i];

			if (newX >= 0 && newX < nrColoane && newY >= 0 && newY < nrLinii && !vizitat[newY][newX] && !matriceObstacole[newY][newX]) {
				vizitat[newY][newX] = true;
				parinte[newY][newX] = current;
				coada.push({ newX, newY });
			}
		}
	}

	vector<Punct> drum;
	if (!vizitat[stop.y][stop.x]) {
		cout << "Nu exista drum!" << endl;
		return drum;
	}

	Punct current = stop;
	while (current.x != -1 && current.y != -1) {
		drum.push_back(current);
		current = parinte[current.y][current.x];
	}

	reverse(drum.begin(), drum.end());
	return drum;
}


void plasareLinieInMatrice(const Nod* nod1, const Nod* nod2, vector<vector<bool>>& matriceObstacole, int nrLinii, int nrColoane, float marimeCasuta)
{
	constexpr float marimeSpatiu = 15.0f;
	const float inaltimeSimbol1 = nod1->date.inaltimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol2 = nod2->date.inaltimeSimbol / 2 + marimeSpatiu;
	Punct start = {
	interval(static_cast<int>(nod1->date.x / marimeCasuta), 0, nrColoane - 1),
	interval(static_cast<int>((nod1->date.y) / marimeCasuta + 1), 0, nrLinii - 1)
	};

	Punct stop = {
		interval(static_cast<int>(nod2->date.x / marimeCasuta), 0, nrColoane - 1),
		interval(static_cast<int>((nod2->date.y) / marimeCasuta - 1), 0, nrLinii - 1)
	};

	//plaseaza o linie in matrice pornind din mijlocul simbolului 1 in jos de lungime marimeSpatiu (15px)
	for (int i = start.y; i <= start.y + static_cast<int>(inaltimeSimbol1 / marimeCasuta); i++)
	{
		matriceObstacole[i][start.x] = true;
	}
	start.y = interval(start.y + static_cast<int>(inaltimeSimbol1 / marimeCasuta), 0, nrLinii - 1);

	//plaseaza o linie in matrice pornind din mijlocul simbolului 2 in sus de lungime marimeSpatiu (15px)
	for (int i = stop.y; i >= stop.y - static_cast<int>(inaltimeSimbol2 / marimeCasuta); i--)
	{
		matriceObstacole[i][stop.x] = true;
	}
	stop.y = interval(stop.y - static_cast<int>(inaltimeSimbol2 / marimeCasuta), 0, nrLinii - 1);

	//BFS din punctul (startX, startY) pana la (stopX, stopY) pentru a plasa linia in matrice
	vector<Punct> drum = gasesteDrumBFS(matriceObstacole, start, stop, nrLinii, nrColoane);
	for (const auto& punct : drum)
		matriceObstacole[punct.y][punct.x] = true;
}

void plasareSimbolInMatrice(const Nod* nodDePlasat, vector<vector<bool>>& matriceObstacole, int nrLinii, int nrColoane, float marimeCasuta)
{
	constexpr float marimeSpatiu = 0.0f;
	const float lungimeSimbol = nodDePlasat->date.lungimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol = nodDePlasat->date.inaltimeSimbol / 2 + marimeSpatiu;

	// Converteste simbolurile in coordonatele matricei
	const int startX = max(static_cast<int>((nodDePlasat->date.x - lungimeSimbol) / marimeCasuta), 0);
	const int startY = max(static_cast<int>((nodDePlasat->date.y - inaltimeSimbol) / marimeCasuta), 0);
	const int stopX = min(static_cast<int>((nodDePlasat->date.x + lungimeSimbol) / marimeCasuta), nrColoane - 1);
	const int stopY = min(static_cast<int>((nodDePlasat->date.y + inaltimeSimbol) / marimeCasuta), nrLinii - 1);

	//Plaseaza spatiile ocupate de simbol in matricea de obstacole
	for (int linie = startY; linie <= stopY; linie++)
		for (int coloana = startX; coloana <= stopX; coloana++)
			matriceObstacole[linie][coloana] = true;
}

void plasareSimboluriRec(const Nod* nodCurent, vector<vector<bool>>& matriceObstacole, int nrLinii, int nrColoane, float marimeCasuta)
{
	static unordered_set<const Nod*> noduriVizitate;

	noduriVizitate.insert(nodCurent);
	plasareSimbolInMatrice(nodCurent, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
	if (nodCurent->st != nullptr && noduriVizitate.count(nodCurent->st) == 0) {
		plasareSimboluriRec(nodCurent->st, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
		plasareLinieInMatrice(nodCurent, nodCurent->st, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
	}
	if (nodCurent->dr != nullptr && noduriVizitate.count(nodCurent->dr) == 0) {
		plasareSimboluriRec(nodCurent->dr, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
		plasareLinieInMatrice(nodCurent, nodCurent->dr, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
	}
	noduriVizitate.erase(nodCurent);
}

void plasareSimboluriListaArbori(vector<vector<bool>>& matriceObstacole, int nrLinii, int nrColoane, float marimeCasuta)
{
	for (const auto& arbore : listaArbori)
		plasareSimboluriRec(arbore.radacina, matriceObstacole, nrLinii, nrColoane, marimeCasuta);
}

void actualizareLinii(const VideoMode& desktop)
{
	constexpr int marimeCasuta = 20;
	const int nrLinii = static_cast<int>(desktop.height) / marimeCasuta + 1;
	const int nrColoane = static_cast<int>(desktop.width) / marimeCasuta + 1;
	vector<vector<bool>> matriceObstacole(nrLinii, vector<bool>(nrColoane, false));
	plasareSimboluriListaArbori(matriceObstacole, nrLinii, nrColoane, marimeCasuta);

	for (int i = 0; i < nrLinii; ++i) {
		for (int j = 0; j < nrColoane; ++j)
			if (matriceObstacole[i][j])
				cout << "X ";
			else
				cout << ". ";
		cout << '\n';
	}
	cout << endl;
}
