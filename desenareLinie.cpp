#include "desenareLinie.h"
#include <queue>
#define PI 3.14159265358979323846
struct Punct {
	int x_matrice;
	int y_matrice;
	float x_ecran;
	float y_ecran;
};

struct Linie
{
	vector<Punct> coordonate;
	Color culoareLinie = Color::Black;
	Nod* nodStart, * nodStop;
};

vector<Linie> liniiDeDesenat;
int nrLinii, nrColoane, marimeCasuta;
constexpr float marimeSpatiu = 20.0f;
vector<vector<short int>> matriceObstacole;


int interval(int valoare, int min, int max)
{
	if (valoare < min)
		return min;
	if (valoare > max)
		return max;
	return valoare;
}

void convertesteVectorInCoordMatrice(vector<Punct>& puncte)
{
	for (auto& punct : puncte)
	{
		punct.x_matrice = interval(punct.x_ecran / marimeCasuta, 0, nrColoane - 1);
		punct.y_matrice = interval(punct.y_ecran / marimeCasuta, 0, nrLinii - 1);
	}
}

int convertesteInCoordMatrice(const float valoare)
{
	return static_cast<int>(valoare) / marimeCasuta;
}

void convertesteVectorInCoordEcran(vector<Punct>& puncte) {
	for (auto& punct : puncte) {
		punct.x_ecran = punct.x_matrice * marimeCasuta + marimeCasuta / 2;
		punct.y_ecran = punct.y_matrice * marimeCasuta + marimeCasuta / 2;
	}
}

float convertesteInCoordEcran(float valoare)
{
	return valoare * marimeCasuta;
}

void afisareMatriceObstacole()
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane; j++) {
			if (matriceObstacole[i][j] < 0)
				cout << "X ";
			else if (matriceObstacole[i][j] > 0)
				cout << matriceObstacole[i][j] << " ";
			else
				cout << ". ";
		}
		cout << endl;
	}
}

vector<Punct> optimizareDrumBFS(const vector<Punct>& drum)
{
	vector<Punct> drumOptimizat;
	if (!drum.empty()) {
		drumOptimizat.push_back(drum[0]);
		int dirX = 0, dirY = 0;

		for (size_t i = 1; i < drum.size(); ++i) {
			const int diffX = drum[i].x_matrice - drum[i - 1].x_matrice;
			const int diffY = drum[i].y_matrice - drum[i - 1].y_matrice;

			if ((diffX == dirX && diffY == dirY) || (diffX == 0 && diffY == 0)) {
				continue;
			}
			if (!(drumOptimizat.back().x_matrice == drum[i - 1].x_matrice && drumOptimizat.back().y_matrice == drum[i - 1].y_matrice)) {
				drumOptimizat.push_back(drum[i - 1]);
			}

			dirX = diffX;
			dirY = diffY;
		}
		drumOptimizat.push_back(drum.back());

		for (size_t i = 1; i < drumOptimizat.size(); ++i)
		{
			const int diffX = drumOptimizat[i].x_matrice - drumOptimizat[i - 1].x_matrice;
			const int diffY = drumOptimizat[i].y_matrice - drumOptimizat[i - 1].y_matrice;

			if (diffX == 0) {
				drumOptimizat[i].x_ecran = drumOptimizat[i - 1].x_ecran;
			}
			if (diffY == 0) {
				drumOptimizat[i].y_ecran = drumOptimizat[i - 1].y_ecran;
			}
		}

		if (drumOptimizat.size() > 1 && drumOptimizat.back().x_matrice == drumOptimizat[drumOptimizat.size() - 2].x_matrice)
			drumOptimizat.back().x_ecran = drumOptimizat[drumOptimizat.size() - 2].x_ecran;
	}
	return drumOptimizat;
}

vector<Punct> gasesteDrumBFS(const Punct& start, const Punct& stop) {
	vector<vector<bool>> vizitat(nrLinii, vector<bool>(nrColoane, false));
	vector<vector<Punct>> parinte(nrLinii, vector<Punct>(nrColoane, { -1, -1 }));

	queue<Punct> coada;
	coada.push(start);
	vizitat[start.y_matrice][start.x_matrice] = true;

	constexpr int dirX[] = { -1, 1,0, 0 };
	constexpr int dirY[] = { 0, 0,1, -1 };

	while (!coada.empty()) {
		const Punct current = coada.front();
		coada.pop();

		if (current.x_matrice == stop.x_matrice && current.y_matrice == stop.y_matrice) {
			break;
		}

		for (int i = 0; i < 4; ++i) {
			const int newX = current.x_matrice + dirX[i];
			const int newY = current.y_matrice + dirY[i];

			if (newX >= 0 && newX < nrColoane && newY >= 0 && newY < nrLinii && !vizitat[newY][newX] && matriceObstacole[newY][newX] == 0) {
				vizitat[newY][newX] = true;
				parinte[newY][newX] = current;
				coada.push({ newX, newY, convertesteInCoordEcran(newX), convertesteInCoordEcran(newY) });
			}
		}
	}

	vector<Punct> drum;
	if (!vizitat[stop.y_matrice][stop.x_matrice]) {
		return drum;
	}
	Punct current = stop;
	while (current.x_matrice != -1 && current.y_matrice != -1) {
		drum.push_back(current);
		current = parinte[current.y_matrice][current.x_matrice];
	}
	reverse(drum.begin(), drum.end());
	return optimizareDrumBFS(drum);
}

void plaseazaDrumInMatrice(const vector<Punct>& drumOptimizat, const int short valoareDeSetat) {
	//algoritmul Bresenham pentru a desena linii intre puncte
	if (drumOptimizat.size() < 2)
	{
		return;
	}
	for (size_t i = 0; i < drumOptimizat.size() - 1; ++i) {
		const Punct& punctStart = drumOptimizat[i];
		const Punct& punctStop = drumOptimizat[i + 1];

		int startX = punctStart.x_matrice;
		int startY = punctStart.y_matrice;
		const int deltaX = abs(punctStop.x_matrice - startX);
		const int deltaY = abs(punctStop.y_matrice - startY);
		const int semnX = startX < punctStop.x_matrice ? 1 : -1;
		const int semnY = startY < punctStop.y_matrice ? 1 : -1;

		int eroare = deltaX - deltaY;

		while (startX != punctStop.x_matrice || startY != punctStop.y_matrice) {
			matriceObstacole[startY][startX] = valoareDeSetat;
			const int eroare2 = eroare * 2;
			if (eroare2 > -deltaY) {
				eroare -= deltaY;
				startX += semnX;
			}
			if (eroare2 < deltaX) {
				eroare += deltaX;
				startY += semnY;
			}
		}
		matriceObstacole[punctStop.y_matrice][punctStop.x_matrice] = valoareDeSetat;
	}
}

void plaseazaLinieObstacol(const Punct& start, const Punct& stop, const short int idLinie)
{
	const vector<Punct> drumOptimizat = gasesteDrumBFS(start, stop);
	plaseazaDrumInMatrice(drumOptimizat, liniiDeDesenat.size() + 1);
	Linie linie;
	linie.coordonate = drumOptimizat;
	if (drumOptimizat.empty()) {
		return;
	}
	if (idLinie == -1) {
		liniiDeDesenat.push_back(linie);
	}
	else {
		liniiDeDesenat[idLinie] = linie;
	}
}

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2)
{
	const float inaltimeSimbol1 = nod1->date.inaltimeSimbol / 2;
	const float inaltimeSimbol2 = nod2->date.inaltimeSimbol / 2;

	for (int i = convertesteInCoordMatrice(nod1->date.y + inaltimeSimbol1); i <= convertesteInCoordMatrice(nod1->date.y + inaltimeSimbol1 + marimeSpatiu); i++)
		matriceObstacole[i][convertesteInCoordMatrice(nod1->date.x)] = 0;
	for (int i = convertesteInCoordMatrice(nod2->date.y - inaltimeSimbol2); i >= convertesteInCoordMatrice(nod2->date.y - inaltimeSimbol2 - marimeSpatiu); i--)
		matriceObstacole[i][convertesteInCoordMatrice(nod2->date.x)] = 0;

	const Punct start = {
	interval(convertesteInCoordMatrice(nod1->date.x), 0, nrColoane - 1),
	interval(convertesteInCoordMatrice(nod1->date.y + inaltimeSimbol1), 0, nrLinii - 1),
		nod1->date.x,
		nod1->date.y + inaltimeSimbol1
	};
	const Punct stop = {
		interval(convertesteInCoordMatrice(nod2->date.x), 0, nrColoane - 1),
		interval(convertesteInCoordMatrice(nod2->date.y - inaltimeSimbol2), 0, nrLinii - 1),
		nod2->date.x,
		nod2->date.y - inaltimeSimbol2
	};
	plaseazaLinieObstacol(start, stop, -1);
	liniiDeDesenat.back().nodStart = const_cast<Nod*>(nod1);
	liniiDeDesenat.back().nodStop = const_cast<Nod*>(nod2);
}

void stergereLiniiObstacoleCuNodulDat(const Nod* nod) {
	if (liniiDeDesenat.empty()) {
		return;
	}
	const float inaltimeSimbol = nod->date.inaltimeSimbol / 2;
	for (auto it = liniiDeDesenat.begin(); it != liniiDeDesenat.end();) {
		if (it->coordonate.size() >= 2) {
			const Punct& punctStart = it->coordonate.front();
			const Punct& punctStop = it->coordonate.back();

			if ((punctStart.x_matrice - convertesteInCoordMatrice(nod->date.x) == 0 && punctStart.y_matrice - (convertesteInCoordMatrice(nod->date.y + inaltimeSimbol)) == 0) ||
				(punctStop.x_matrice - convertesteInCoordMatrice(nod->date.x) == 0 && punctStop.y_matrice - (convertesteInCoordMatrice(nod->date.y - inaltimeSimbol)) == 0))
			{
				plaseazaDrumInMatrice(it->coordonate, 0);
				it = liniiDeDesenat.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}
	for (size_t i = 0; i < liniiDeDesenat.size(); ++i) {
		plaseazaDrumInMatrice(liniiDeDesenat[i].coordonate, i + 1);
	}
}

void actualizeazaLinieObstacolPrinId(const int idLinie, const Nod* nodDeMutat)
{
	if (idLinie < 1 || idLinie > liniiDeDesenat.size())
		return;
	const Punct start = liniiDeDesenat[idLinie - 1].coordonate.front();
	const Punct stop = liniiDeDesenat[idLinie - 1].coordonate.back();
	plaseazaDrumInMatrice(liniiDeDesenat[idLinie - 1].coordonate, 0);
	adaugaSimbolCaObstacole(nodDeMutat);
	plaseazaLinieObstacol(start, stop, idLinie - 1);//actualizeaza linia Suprapusa de nodDeMutat
}

void modificareSimbolObstacol(const Nod* nod, const short int valoareDeSetat)
{
	const float lungimeSimbol = nod->date.lungimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol = nod->date.inaltimeSimbol / 2 + marimeSpatiu;

	const int startX = max(convertesteInCoordMatrice(nod->date.x - lungimeSimbol), 0);
	const int startY = max(convertesteInCoordMatrice(nod->date.y - inaltimeSimbol), 0);
	const int stopX = min(convertesteInCoordMatrice(nod->date.x + lungimeSimbol), nrColoane - 1);
	const int stopY = min(convertesteInCoordMatrice(nod->date.y + inaltimeSimbol), nrLinii - 1);

	//Spatiile ocupate de simbol in matrice sunt marcate cu valoareDeSetat 
	for (int linie = startY; linie <= stopY; linie++)
		for (int coloana = startX; coloana <= stopX; coloana++)
			matriceObstacole[linie][coloana] = valoareDeSetat;
}

void adaugaSimbolCaObstacole(const Nod* nod)
{
	modificareSimbolObstacol(nod, -1);
}

void stergeSimbolObstacol(const Nod* nod)
{
	modificareSimbolObstacol(nod, 0);
}

void initializareMatriceObstacole(const VideoMode& desktop)
{
	marimeCasuta = 20;
	nrLinii = static_cast<int>(desktop.height) / marimeCasuta + 1;
	nrColoane = static_cast<int>(desktop.width) / marimeCasuta + 1;
	matriceObstacole = vector<vector<short int>>(nrLinii, vector<short int>(nrColoane, false));
}

short verificareSuprapunere(const Nod* nod)
{
	const float lungimeSimbol = nod->date.lungimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol = nod->date.inaltimeSimbol / 2 + marimeSpatiu;

	const int startX = max(convertesteInCoordMatrice(nod->date.x - lungimeSimbol), 0);
	const int startY = max(convertesteInCoordMatrice(nod->date.y - inaltimeSimbol), 0);
	const int stopX = min(convertesteInCoordMatrice(nod->date.x + lungimeSimbol), nrColoane - 1);
	const int stopY = min(convertesteInCoordMatrice(nod->date.y + inaltimeSimbol), nrLinii - 1);

	for (int linie = startY; linie <= stopY; linie++) {
		if (matriceObstacole[linie][startX] != 0)
			return matriceObstacole[linie][startX];
		if (matriceObstacole[linie][stopX] != 0)
			return matriceObstacole[linie][stopX];
	}
	for (int coloane = startX + 1; coloane < stopX; coloane++) {
		if (matriceObstacole[startY][coloane] != 0)
			return matriceObstacole[startY][coloane];
		if (matriceObstacole[stopY][coloane] != 0)
			return matriceObstacole[stopY][coloane];
	}
	return 0;
}


bool verificareSimbolInZonaMatriceObstacole(const Nod* nod1, const Nod* nod2) {
	return (abs(nod1->date.x - nod2->date.x) < nod1->date.lungimeSimbol / 2 + nod2->date.lungimeSimbol / 2 + marimeSpatiu &&
		abs(nod1->date.y - nod2->date.y) < nod1->date.inaltimeSimbol / 2 + nod2->date.inaltimeSimbol / 2 + marimeSpatiu);
}

Nod* gasesteNodObstacolRec(Nod* nodCurent, Nod*& nodCautat, unordered_set<const Nod*> noduriVizitate) {
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent))
		return nullptr;
	if (verificareSimbolInZonaMatriceObstacole(nodCautat, nodCurent))
		return nodCurent;

	noduriVizitate.insert(nodCurent);
	Nod* nodGasit = gasesteNodObstacolRec(nodCurent->st, nodCautat, noduriVizitate);
	if (nodGasit != nullptr)
		return nodGasit;
	return gasesteNodObstacolRec(nodCurent->dr, nodCautat, noduriVizitate);
}

Nod* gasesteNodObstacol(Nod* nodCurent, Nod*& nodCautat) {
	const unordered_set<const Nod*> noduriVizitate;
	return gasesteNodObstacolRec(nodCurent, nodCautat, noduriVizitate);
}

Nod* gasesteNodObstacolInLista(Nod*& nod) {
	for (const auto& arbore : listaArbori)
	{
		Nod* nodCautat = gasesteNodObstacol(arbore.radacina, nod);
		if (nodCautat != nullptr)
			return nodCautat;
	}
	return nullptr;
}

void desenareTriunghi(RenderWindow& fereastraAplicatie, const float x, const float y, const Color culoareLinie, const float lungimeLatura, const float grosimeLinie)
{
	ConvexShape triunghi;
	triunghi.setPointCount(3);

	const float inaltime = lungimeLatura * sqrt(3) / 2;
	triunghi.setPoint(0, Vector2f(0, 0));
	triunghi.setPoint(1, Vector2f(lungimeLatura / 2, inaltime));
	triunghi.setPoint(2, Vector2f(lungimeLatura, 0));

	triunghi.setOrigin(0, 0);
	triunghi.setPosition(x - lungimeLatura / 2 - grosimeLinie, y - inaltime + grosimeLinie);
	triunghi.setFillColor(culoareLinie);
	fereastraAplicatie.draw(triunghi);
}

void desenareSegmentLinie(RenderWindow& fereastraAplicatie, const float x1, const float y1, const float x2, const float y2, const Color culoareLinie, const float grosimeLinie)
{
	RectangleShape linie(Vector2f(0, grosimeLinie));
	const float x = x2 - x1;
	const float y = y2 - y1;
	const float lng = sqrt(x * x + y * y);
	const float unghi = static_cast<float>(atan2(y, x) * 180 / (PI));

	linie.setSize(Vector2f(lng, grosimeLinie));
	linie.setPosition(x1, y1);
	linie.setRotation(unghi);
	linie.setFillColor(culoareLinie);
	fereastraAplicatie.draw(linie);
}

void desenareLinie(RenderWindow& fereastraAplicatie, const Linie& linie) {
	if (linie.coordonate.size() < 2) {
		return;
	}

	constexpr float grosimeLinie = 6;
	for (size_t i = 0; i < linie.coordonate.size() - 1; ++i) {
		const auto coordonateCurente = linie.coordonate[i];
		const auto coordonateUrmatoare = linie.coordonate[i + 1];
		const auto culoareLinie = linie.culoareLinie;
		desenareSegmentLinie(fereastraAplicatie, coordonateCurente.x_ecran, coordonateCurente.y_ecran, coordonateUrmatoare.x_ecran, coordonateUrmatoare.y_ecran, culoareLinie, grosimeLinie);
	}

	if (!linie.coordonate.empty()) {
		constexpr float lungimeLaturaTriunghi = 40;
		const auto ultimaCoordonata = linie.coordonate.back();
		desenareTriunghi(fereastraAplicatie, ultimaCoordonata.x_ecran, ultimaCoordonata.y_ecran, linie.culoareLinie, lungimeLaturaTriunghi, grosimeLinie);
	}
}

void desenareLinii(RenderWindow& fereastraAplicatie)
{
	for (const auto& linie : liniiDeDesenat)
		desenareLinie(fereastraAplicatie, linie);
}