#include "desenareLinie.h"
#include <queue>
#define PI 3.14159265358979323846
struct Punct
{
	int x;
	int y;
};

struct Linie
{
	vector<Punct> coordonateMatrice;
	vector<Punct> coordonateEcran;
	Color culoareLinie = Color::Black;
};

vector<Linie> liniiDeDesenat;
int nrLinii, nrColoane, marimeCasuta;
vector<vector<bool>> matriceObstacole;


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
		punct.x = interval(punct.x / marimeCasuta, 0, nrColoane - 1);
		punct.y = interval(punct.y / marimeCasuta, 0, nrLinii - 1);
	}
}

int convertesteInCoordMatrice(const float valoare)
{
	return static_cast<int>(valoare) / marimeCasuta;
}

void convertesteInCoordEcran(vector<Punct>& puncte) {
	for (auto& punct : puncte) {
		punct.x = punct.x * marimeCasuta + marimeCasuta / 2;
		punct.y = punct.y * marimeCasuta + marimeCasuta / 2;
	}
}

vector<Punct> gasesteDrumBFS(const Punct& start, const Punct& stop) {
	vector<vector<bool>> vizitat(nrLinii, vector<bool>(nrColoane, false));
	vector<vector<Punct>> parinte(nrLinii, vector<Punct>(nrColoane, { -1, -1 }));

	queue<Punct> coada;
	coada.push(start);
	vizitat[start.y][start.x] = true;

	constexpr int dirX[] = { -1, 1,0, 0 };
	constexpr int dirY[] = { 0, 0,1, -1 };

	while (!coada.empty()) {
		const Punct current = coada.front();
		coada.pop();

		if (current.x == stop.x && current.y == stop.y) {
			break;
		}

		for (int i = 0; i < 4; ++i) {
			const int newX = current.x + dirX[i];
			const int newY = current.y + dirY[i];

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

	vector<Punct> drumOptimizat;
	if (!drum.empty()) {
		drumOptimizat.push_back(drum[0]);
		int dirX = 0, dirY = 0;
		for (size_t i = 1; i < drum.size(); ++i) {
			const int diffX = drum[i].x - drum[i - 1].x;
			const int diffY = drum[i].y - drum[i - 1].y;

			if ((diffX == dirX && diffY == dirY) || (diffX == 0 && diffY == 0)) {
				continue;
			}

			drumOptimizat.push_back(drum[i - 1]);
			dirX = diffX;
			dirY = diffY;
		}
		drumOptimizat.push_back(drum.back());
	}
	return drumOptimizat;
}

void plaseazaDrumInMatrice(const vector<Punct>& drumOptimizat, const bool valoareDeSetat) {
	//algoritmul Bresenham
	for (size_t i = 0; i < drumOptimizat.size() - 1; ++i) {
		const Punct& punctStart = drumOptimizat[i];
		const Punct& punctStop = drumOptimizat[i + 1];

		int startX = punctStart.x;
		int startY = punctStart.y;
		const int deltaX = abs(punctStop.x - startX);
		const int deltaY = abs(punctStop.y - startY);
		const int semnX = startX < punctStop.x ? 1 : -1;
		const int semnY = startY < punctStop.y ? 1 : -1;

		int eroare = deltaX - deltaY;

		while (startX != punctStop.x || startY != punctStop.y) {
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
	}
}

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2)
{
	constexpr float marimeSpatiu = 20.0f;
	const float inaltimeSimbol1 = nod1->date.inaltimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol2 = nod2->date.inaltimeSimbol / 2 + marimeSpatiu;
	const Punct start = {
	interval(convertesteInCoordMatrice(nod1->date.x), 0, nrColoane - 1),
	interval(convertesteInCoordMatrice(nod1->date.y + inaltimeSimbol1) + 1, 0, nrLinii - 1)
	};
	const Punct stop = {
		interval(convertesteInCoordMatrice(nod2->date.x), 0, nrColoane - 1),
		interval(convertesteInCoordMatrice(nod2->date.y - inaltimeSimbol2) - 1, 0, nrLinii - 1)
	};

	const vector<Punct> drumOptimizat = gasesteDrumBFS(start, stop);
	plaseazaDrumInMatrice(drumOptimizat, true);
	Linie linie;
	linie.coordonateEcran = drumOptimizat;
	liniiDeDesenat.push_back(linie);

}

void stergereLinieObstacol(const Nod* nod)
{
	for (auto it = liniiDeDesenat.begin(); it != liniiDeDesenat.end();)
	{
		if ((it->coordonateMatrice[0].x == nod->date.x && it->coordonateMatrice[0].y == nod->date.y) ||
			(it->coordonateMatrice.back().x == nod->date.x && it->coordonateMatrice.back().y == nod->date.y))
		{
			plaseazaDrumInMatrice(it->coordonateMatrice, false);
			it = liniiDeDesenat.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void modificareSimbolObstacol(const Nod* nod, bool valoareDeSetat)
{
	constexpr float marimeSpatiu = 20.0f;
	const float lungimeSimbol = nod->date.lungimeSimbol / 2 + marimeSpatiu;
	const float inaltimeSimbol = nod->date.inaltimeSimbol / 2 + marimeSpatiu;

	// Converteste punctele in coordonatele matricei
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
	modificareSimbolObstacol(nod, true);
}

void stergeSimbolObstacol(const Nod* nod)
{
	modificareSimbolObstacol(nod, false);
}


void initializareMatriceObstacole(const VideoMode& desktop)
{
	marimeCasuta = 20;
	nrLinii = static_cast<int>(desktop.height) / marimeCasuta + 1;
	nrColoane = static_cast<int>(desktop.width) / marimeCasuta + 1;
	matriceObstacole = vector<vector<bool>>(nrLinii, vector<bool>(nrColoane, false));
}

void desenareSegmentLinie(RenderWindow& fereastraAplicatie, float x1, float y1, float x2, float y2, Color culoareLinie)
{
	constexpr float grosimeLinie = 3;
	RectangleShape linie(Vector2f(0, grosimeLinie));

	float spatiu = 55;
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
	if (linie.coordonateEcran.size() < 2) {
		return;
	}

	for (size_t i = 0; i < linie.coordonateEcran.size() - 1; ++i) {
		const auto coordonateCurente = linie.coordonateEcran[i];
		const auto coordonateUrmatoare = linie.coordonateEcran[i + 1];
		const auto culoareLinie = linie.culoareLinie;
		desenareSegmentLinie(fereastraAplicatie, coordonateCurente.x, coordonateCurente.y, coordonateUrmatoare.x, coordonateUrmatoare.y, culoareLinie);
	}
}

void desenareLinii(RenderWindow& fereastraAplicatie)
{
	for (const auto& linie : liniiDeDesenat)
		desenareLinie(fereastraAplicatie, linie);
}
