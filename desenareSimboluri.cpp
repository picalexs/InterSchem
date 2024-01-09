#include "desenareSimboluri.h"
#include "executareAlgoritm.h"
#include "functiiNod.h"
#define PI 3.14159265358979323846

struct PunctDesen
{
	float x;
	float y;
};

PunctDesen dateNodInPunctDesen(const DateNod& date)
{
	PunctDesen PunctDesen;
	PunctDesen.x = date.x;
	PunctDesen.y = date.y;
	return PunctDesen;
}

void desenareLinie(RenderWindow& fereastraAplicatie, const PunctDesen& pA, const PunctDesen& pB, const float& grosime, const Color& culoareSimbol) {
	const float lungime = sqrt((pB.x - pA.x) * (pB.x - pA.x) + (pB.y - pA.y) * (pB.y - pA.y));
	const float unghi = static_cast<float> (atan2(pB.y - pA.y, pB.x - pA.x) * 180 / PI);

	RectangleShape line(Vector2f(lungime, grosime));
	line.rotate(unghi);
	line.setPosition(pA.x, pA.y);
	line.setFillColor(culoareSimbol);
	fereastraAplicatie.draw(line);
}

void desenareDreptunghi(RenderWindow& fereastraAplicatie, const PunctDesen& centru, const float& lungime, const float& latime, const Color& culoareSimbol) {
	PunctDesen pNE, pSE, pSV, pNV;
	pNE.x = pSE.x = centru.x + lungime / 2;
	pNV.x = pSV.x = centru.x - lungime / 2;
	pNE.y = pNV.y = centru.y - latime / 2;
	pSE.y = pSV.y = centru.y + latime / 2;

	ConvexShape dreptunghi;
	dreptunghi.setPointCount(4);
	dreptunghi.setPoint(0, Vector2f(pNE.x, pNE.y));
	dreptunghi.setPoint(1, Vector2f(pSE.x, pSE.y));
	dreptunghi.setPoint(2, Vector2f(pSV.x, pSV.y));
	dreptunghi.setPoint(3, Vector2f(pNV.x, pNV.y));
	dreptunghi.setFillColor(culoareSimbol);
	fereastraAplicatie.draw(dreptunghi);
}

void desenareClopote(RenderWindow& fereastraAplicatie, const PunctDesen& centru, const float& lungime, const float& inaltime, const int& calitate, const Color& culoareSimbol, const Color& culoareDA, const Color& culoareNU) {
	ConvexShape clopoteDA, clopoteNU;
	clopoteDA.setPointCount(calitate / 4 + 2);
	clopoteNU.setPointCount(calitate / 4 + 2);
	for (int i = 0; i <= calitate / 4; i++) {
		const double rad = (360.0 / calitate * i + 180) / (360.0 / PI / 2);
		const float x = static_cast<float>(cos(rad) * inaltime);
		const float y = static_cast<float>(sin(rad) * inaltime);
		clopoteDA.setPoint(i, Vector2f(x + inaltime - lungime / 2, y + inaltime / 2));
		clopoteNU.setPoint(i, Vector2f(lungime / 2 - inaltime - x, y + inaltime / 2));

	}
	Vector2f primulPunctDesen = clopoteDA.getPoint(0);
	Vector2f ultimulPunctDesen = clopoteDA.getPoint(calitate / 4);
	clopoteDA.setPoint(calitate / 4 + 1, Vector2f(ultimulPunctDesen.x, primulPunctDesen.y));
	clopoteDA.setPosition(centru.x, centru.y);
	clopoteDA.setFillColor(culoareDA);
	fereastraAplicatie.draw(clopoteDA);

	primulPunctDesen = clopoteNU.getPoint(0);
	ultimulPunctDesen = clopoteNU.getPoint(calitate / 4);
	clopoteNU.setPoint(calitate / 4 + 1, Vector2f(ultimulPunctDesen.x, primulPunctDesen.y));
	clopoteNU.setPosition(centru.x, centru.y);
	clopoteNU.setFillColor(culoareNU);
	fereastraAplicatie.draw(clopoteNU);

	desenareDreptunghi(fereastraAplicatie, centru, lungime - inaltime * 2, inaltime, culoareSimbol);

}

void desenareElipsa(RenderWindow& fereastraAplicatie, const PunctDesen& centru, const float& raza_x, const float& raza_y, const int& calitate, const Color& culoareSimbol)
{
	ConvexShape elipsa;
	elipsa.setPointCount(calitate);
	for (int i = 0; i < calitate; i++) {
		const double rad = (360.0 / calitate * i) / (360 / PI / 2);
		const float x = static_cast<float>(cos(rad)) * raza_x;
		const float y = static_cast<float>(sin(rad)) * raza_y;
		elipsa.setPoint(i, Vector2f(x, y));
	}

	elipsa.setPosition(centru.x, centru.y);
	elipsa.setFillColor(culoareSimbol);
	fereastraAplicatie.draw(elipsa);
}

void desenareCapsula(RenderWindow& fereastraAplicatie, const PunctDesen& centru, const float& raza_x, const float& raza_y, const int& calitate, const Color& culoareSimbol)
{
	PunctDesen centruDr;
	PunctDesen centruSt = centruDr = centru;
	const float razaNoua = raza_x - raza_y;
	centruSt.x -= razaNoua / 2;
	centruDr.x += razaNoua / 2;
	desenareElipsa(fereastraAplicatie, centruSt, raza_y / 2, raza_y / 2, calitate, culoareSimbol);
	desenareElipsa(fereastraAplicatie, centruDr, raza_y / 2, raza_y / 2, calitate, culoareSimbol);
	desenareDreptunghi(fereastraAplicatie, centru, razaNoua, raza_y, culoareSimbol);
}

void desenareTrapez(RenderWindow& fereastraAplicatie, const PunctDesen& centru, const float& bazaMica, const float& bazaMare, const float& inaltime, const Color& culoareSimbol)
{
	PunctDesen pStangaSus, pDreaptaSus, pStangaJos, pDreaptaJos;
	pStangaSus.x = centru.x - bazaMica / 2;
	pDreaptaSus.x = centru.x + bazaMica / 2;
	pStangaJos.x = centru.x - bazaMare / 2;
	pDreaptaJos.x = centru.x + bazaMare / 2;
	pStangaSus.y = pDreaptaSus.y = centru.y - inaltime / 2;
	pStangaJos.y = pDreaptaJos.y = centru.y + inaltime / 2;

	ConvexShape trapez;
	trapez.setPointCount(4);
	trapez.setPoint(0, Vector2f(pStangaSus.x, pStangaSus.y));
	trapez.setPoint(1, Vector2f(pStangaJos.x, pStangaJos.y));
	trapez.setPoint(2, Vector2f(pDreaptaJos.x, pDreaptaJos.y));
	trapez.setPoint(3, Vector2f(pDreaptaSus.x, pDreaptaSus.y));
	trapez.setFillColor(culoareSimbol);
	fereastraAplicatie.draw(trapez);
}

void desenareNodStart(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol) {
	constexpr int calitate = 18;
	const float raza_y = date.inaltimeSimbol;
	const float raza_x = date.lungimeSimbol;
	const PunctDesen centru = dateNodInPunctDesen(date);
	desenareCapsula(fereastraAplicatie, centru, raza_x + 8, raza_y + 8, calitate, culoareSimbol);
}


void desenareNodStop(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol) {
	desenareNodStart(fereastraAplicatie, date, culoareSimbol);
}

void desenareNodAtribuire(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol) {
	const float latimeSimbol = date.inaltimeSimbol;
	const float lungimeSimbol = date.lungimeSimbol;
	const PunctDesen centru = dateNodInPunctDesen(date);
	desenareDreptunghi(fereastraAplicatie, centru, lungimeSimbol, latimeSimbol, culoareSimbol);
}

void desenareNodCitire(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol) {
	const float inaltimeSimbol = date.inaltimeSimbol;
	const float lungimeSimbol = date.lungimeSimbol;
	const float bazaMare = lungimeSimbol;
	const float bazaMica = bazaMare - 50;
	const float inaltime = inaltimeSimbol;
	const PunctDesen centru = dateNodInPunctDesen(date);
	desenareTrapez(fereastraAplicatie, centru, bazaMica, bazaMare, inaltime, culoareSimbol);
}

void desenareNodAfisare(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol) {
	const float inaltimeSimbol = date.inaltimeSimbol;
	const float lungimeSimbol = date.lungimeSimbol;
	const float bazaMare = lungimeSimbol;
	const float bazaMica = bazaMare - 50;
	const float inaltime = inaltimeSimbol;
	const PunctDesen centru = dateNodInPunctDesen(date);
	desenareTrapez(fereastraAplicatie, centru, bazaMare, bazaMica, inaltime, culoareSimbol);
}

void desenareNodDaca(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol, const Color& culoareDa, const Color& culoareNu) {
	constexpr int calitate = 48;
	const float lungime = date.lungimeSimbol;
	const float latime = date.inaltimeSimbol;
	const PunctDesen centru = dateNodInPunctDesen(date);
	desenareClopote(fereastraAplicatie, centru, lungime, latime, calitate, culoareSimbol, culoareDa, culoareNu);
}


void afisareTextNod(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date)
{
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(date.expresie, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	const float xPos = date.x;
	const float yPos = date.y;
	mainText.setPosition(xPos, yPos);
	fereastraAplicatie.draw(mainText);
}

Color scadereCulori(const Color& color1, const Color& color2) {
	int red = color1.r - color2.r;
	int green = color1.g - color2.g;
	int blue = color1.b - color2.b;

	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	return { static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue) };
}

void determinareCulori(const TipNod tip, const bool& isOutline, Color& culoareSimbol, Color& culoareDa, Color& culoareNu)
{
	switch (tip) {
	case TipNod::START: culoareSimbol = Color(120, 189, 219); break;
	case TipNod::STOP: culoareSimbol = Color(120, 189, 219); break;
	case TipNod::ATRIBUIRE: culoareSimbol = Color(236, 222, 96); break;
	case TipNod::CITIRE: culoareSimbol = Color(102, 210, 102); break;
	case TipNod::AFISARE: culoareSimbol = Color(255, 102, 102); break;
	case TipNod::DACA:
		culoareSimbol = Color(200, 200, 200);
		culoareDa = Color(30, 222, 30);
		culoareNu = Color(212, 68, 52);
		break;
	case TipNod::WHILE:
		culoareSimbol = Color(208, 149, 198);
		culoareDa = Color(30, 222, 30);
		culoareNu = Color(212, 68, 52);
		break;
	default: culoareSimbol = Color::Green; break;
	}

	if (isOutline) {

		const Color culoareOutline(30, 30, 30);
		culoareSimbol = scadereCulori(culoareSimbol, culoareOutline);
		culoareDa = culoareNu = culoareSimbol;
	}
}

void switchDesen(RenderWindow& fereastraAplicatie, const DateNod& date, const Color& culoareSimbol, const Color& culoareDa, const Color& culoareNu)
{
	switch (date.tip) {
	case TipNod::START:
		desenareNodStart(fereastraAplicatie, date, culoareSimbol); break;
	case TipNod::STOP:
		desenareNodStop(fereastraAplicatie, date, culoareSimbol); break;
	case TipNod::ATRIBUIRE:
		desenareNodAtribuire(fereastraAplicatie, date, culoareSimbol); break;
	case TipNod::CITIRE:
		desenareNodCitire(fereastraAplicatie, date, culoareSimbol); break;
	case TipNod::AFISARE:
		desenareNodAfisare(fereastraAplicatie, date, culoareSimbol); break;
	case TipNod::DACA:
	case TipNod::WHILE:
		desenareNodDaca(fereastraAplicatie, date, culoareSimbol, culoareDa, culoareNu); break;
	default:
		break;
	}
}

void creareSimbol(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date, const bool isOutline) {
	Color culoareSimbol;
	Color culoareDa;
	Color culoareNu;
	if (!isOutline)
	{
		const int marimeContur = desktop.height / 125;
		const Color culoareContur = Color(0, 0, 0);
		DateNod dateContur = date;
		dateContur.lungimeSimbol += marimeContur;
		dateContur.inaltimeSimbol += marimeContur;
		switchDesen(fereastraAplicatie, dateContur, culoareSimbol, culoareDa, culoareNu);
	}

	determinareCulori(date.tip, isOutline, culoareSimbol, culoareDa, culoareNu);
	switchDesen(fereastraAplicatie, date, culoareSimbol, culoareDa, culoareNu);

}

void desenareOutline(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& dateNod, const int marimeOutline)
{
	DateNod dateTmp = dateNod;
	dateTmp.lungimeSimbol += marimeOutline;
	dateTmp.inaltimeSimbol += marimeOutline;
	creareSimbol(fereastraAplicatie, desktop, dateTmp, true);
}

void creareSimbolPtArboreRecursiv(RenderWindow& fereastraAplicatie, const VideoMode& desktop, Nod* N, set<const Nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N))
		return;

	const Nod* nodCuOutline = gasesteNodListaCuPozMouse(fereastraAplicatie);
	noduriVizitate.insert(N);
	if (nodCuOutline == N)
	{
		desenareOutline(fereastraAplicatie, desktop, N->date, 30);
	}

	creareSimbol(fereastraAplicatie, desktop, N->date, false);
	afisareTextNod(fereastraAplicatie, desktop, N->date);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, N->st, noduriVizitate);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, N->dr, noduriVizitate);
}

void creareOutlineParcurgereRecursiv(RenderWindow& fereastraAplicatie, const VideoMode& desktop, Nod* N, set<const Nod*>& noduriVizitate)
{
	if (N == nullptr || noduriVizitate.count(N))
		return;
	noduriVizitate.insert(N);
	if (seParcurgeAlgoritmul())
	{
		desenareOutline(fereastraAplicatie, desktop, nodCurentDeParcurgere()->date, 40);
	}
	creareOutlineParcurgereRecursiv(fereastraAplicatie, desktop, N->st, noduriVizitate);
	creareOutlineParcurgereRecursiv(fereastraAplicatie, desktop, N->dr, noduriVizitate);
}

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop) {
	for (const auto& A : listaArbori)
	{
		if (A.radacina == nullptr)
			continue;
		set<const Nod*> noduriVizitate;
		creareOutlineParcurgereRecursiv(fereastraAplicatie, desktop, A.radacina, noduriVizitate);
		noduriVizitate.clear();
		creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, A.radacina, noduriVizitate);
	}
}

