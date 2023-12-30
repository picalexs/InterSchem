#include "desenareSimboluri.h"
#include "functiiNod.h"
#define PI 3.14159265358979323846

struct Punct
{
	float x;
	float y;
};

Punct dateNodInPunct(DateNod& date)
{
	Punct punct;
	punct.x = date.x;
	punct.y = date.y;
	return punct;
}

void desenareLinie(RenderWindow& fereastraAplicatie, const Punct& pA, const Punct& pB, const float& grosime, const Color& culoare) {
	const float lungime = sqrt((pB.x - pA.x) * (pB.x - pA.x) + (pB.y - pA.y) * (pB.y - pA.y));
	const float unghi = static_cast<float> (atan2(pB.y - pA.y, pB.x - pA.x) * 180 / PI);

	RectangleShape line(Vector2f(lungime, grosime));
	line.rotate(unghi);
	line.setPosition(pA.x, pA.y);
	line.setFillColor(culoare);
	fereastraAplicatie.draw(line);
}

void desenareDreptunghi(RenderWindow& fereastraAplicatie, const Punct& centru, const float& lungime, const float& latime, const Color& culoare) {
	Punct pNE, pSE, pSV, pNV;
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
	dreptunghi.setFillColor(culoare);
	fereastraAplicatie.draw(dreptunghi);
}

void desenareClopote(RenderWindow& fereastraAplicatie, const Punct& centru, const float& lungime, const float& inaltime, const int& calitate, const Color& culoareSimbol, const Color& culoareDA, const Color& culoareNU) {
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
	Vector2f primulPunct = clopoteDA.getPoint(0);
	Vector2f ultimulPunct = clopoteDA.getPoint(calitate / 4);
	clopoteDA.setPoint(calitate / 4 + 1, Vector2f(ultimulPunct.x, primulPunct.y));
	clopoteDA.setPosition(centru.x, centru.y);
	clopoteDA.setFillColor(culoareDA);
	fereastraAplicatie.draw(clopoteDA);

	primulPunct = clopoteNU.getPoint(0);
	ultimulPunct = clopoteNU.getPoint(calitate / 4);
	clopoteNU.setPoint(calitate / 4 + 1, Vector2f(ultimulPunct.x, primulPunct.y));
	clopoteNU.setPosition(centru.x, centru.y);
	clopoteNU.setFillColor(culoareNU);
	fereastraAplicatie.draw(clopoteNU);

	desenareDreptunghi(fereastraAplicatie, centru, lungime - inaltime * 2, inaltime, culoareSimbol);

}

void desenareElipsa(RenderWindow& fereastraAplicatie, const Punct& centru, const float& raza_x, const float& raza_y, const int& calitate, const Color& culoare)
{
	ConvexShape elipsa;
	elipsa.setPointCount(calitate);
	for (int i = 0; i < calitate; i++) {
		const double rad = (360.0 / calitate * i) / (360 / PI / 2);
		const float x = cos(rad) * raza_x;
		const float y = sin(rad) * raza_y;
		elipsa.setPoint(i, Vector2f(x, y));
	}

	elipsa.setPosition(centru.x, centru.y);
	elipsa.setFillColor(culoare);
	fereastraAplicatie.draw(elipsa);
}

void desenareCapsula(RenderWindow& fereastraAplicatie, const Punct& centru, const float& raza_x, const float& raza_y, const int& calitate, const Color& culoare)
{
	Punct centruDr;
	Punct centruSt = centruDr = centru;
	const float razaNoua = raza_x - raza_y;
	centruSt.x -= razaNoua / 2;
	centruDr.x += razaNoua / 2;
	desenareElipsa(fereastraAplicatie, centruSt, raza_y / 2, raza_y / 2, calitate, culoare);
	desenareElipsa(fereastraAplicatie, centruDr, raza_y / 2, raza_y / 2, calitate, culoare);
	desenareDreptunghi(fereastraAplicatie, centru, razaNoua, raza_y, culoare);
}

void desenareTrapez(RenderWindow& fereastraAplicatie, const Punct& centru, const float& bazaMica, const float& bazaMare, const float& inaltime, const Color& culoare)
{
	Punct pStangaSus, pDreaptaSus, pStangaJos, pDreaptaJos;
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
	trapez.setFillColor(culoare);
	fereastraAplicatie.draw(trapez);
}

void modificareLungimePtExpresie(const VideoMode& desktop, DateNod& date, const float& lungimeSimbol, float& lungimeDeModificat)
{
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	const Text textExpresie(date.expresie, fontGlobal, marimeFont);
	const float lngText = textExpresie.getLocalBounds().width;
	const float raport = lngText / lungimeSimbol + 0.4f;
	if (raport > 1.0f) {
		lungimeDeModificat *= raport;
	}
}

void desenareNodStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	const Color culoare(120, 189, 219);
	constexpr int calitate = 18;

	float raza_x = date.lungimeSimbol;
	const float raza_y = date.inaltimeSimbol;

	modificareLungimePtExpresie(desktop, date, date.lungimeSimbol, raza_x);

	date.lungimeSimbol = raza_x;
	const Punct centru = dateNodInPunct(date);
	desenareCapsula(fereastraAplicatie, centru, raza_x, raza_y, calitate, culoare);

}


void desenareNodStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	desenareNodStart(fereastraAplicatie, desktop, date);
}

void desenareNodAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	const Color culoare(236, 222, 96);
	const float latimeSimbol = desktop.height / 25;
	const float lungimeSimbol = desktop.width / 15;

	float lungime = lungimeSimbol;
	const float latime = latimeSimbol;

	modificareLungimePtExpresie(desktop, date, lungimeSimbol, lungime);
	date.lungimeSimbol = lungime;

	const Punct centru = dateNodInPunct(date);
	desenareDreptunghi(fereastraAplicatie, centru, lungime, latime, culoare);
}

void desenareNodCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	const Color culoare(102, 210, 102);
	const float inaltimeSimbol = desktop.height / 25;
	const float lungimeSimbol = desktop.width / 15;

	float bazaMare = lungimeSimbol;
	float bazaMica = bazaMare - 50;
	const float inaltime = inaltimeSimbol;

	modificareLungimePtExpresie(desktop, date, lungimeSimbol, bazaMare);
	date.lungimeSimbol = bazaMare;
	bazaMica = bazaMare - 50;
	const Punct centru = dateNodInPunct(date);
	desenareTrapez(fereastraAplicatie, centru, bazaMica, bazaMare, inaltime, culoare);
}

void desenareNodAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	const Color culoare(255, 102, 102);
	const float inaltimeSimbol = desktop.height / 25;
	const float lungimeSimbol = desktop.width / 15;

	float bazaMare = lungimeSimbol;
	float bazaMica = bazaMare - 50;
	const float inaltime = inaltimeSimbol;

	modificareLungimePtExpresie(desktop, date, lungimeSimbol, bazaMare);
	date.lungimeSimbol = bazaMare;
	bazaMica = bazaMare - 50;
	const Punct centru = dateNodInPunct(date);
	desenareTrapez(fereastraAplicatie, centru, bazaMare, bazaMica, inaltime, culoare);
}

void desenareNodDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date) {
	const Color culoareSimbol(192, 192, 192);
	const Color culoareDA(30, 222, 30);
	const Color culoareNU(212, 68, 52);
	constexpr int calitate = 32;
	const float inaltimeSimbol = desktop.height / 25;
	const float lungimeSimbol = desktop.width / 7;

	float lungime = lungimeSimbol;
	const float latime = inaltimeSimbol;
	modificareLungimePtExpresie(desktop, date, lungimeSimbol, lungime);
	date.lungimeSimbol = lungime;

	const Punct centru = dateNodInPunct(date);
	desenareClopote(fereastraAplicatie, centru, lungime, latime, calitate, culoareSimbol, culoareDA, culoareNU);
}

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie) {
	float grosimeLinie = 5;
	RectangleShape line(Vector2f(0, grosimeLinie));
	ConvexShape triunghi(3);

	for (auto& linie : listaLinii) {

		float spatiu = 55;
		float mijlocXNod1 = linie.first.x;
		float mijlocYNod1 = linie.first.y;
		float mijlocXNod2 = linie.second.x;
		float mijlocYNod2 = linie.second.y;

		if (linie.first.tip != 5)
			mijlocYNod1 += 50;
		else
			mijlocYNod1 += 75;

		float x = mijlocXNod2 - mijlocXNod1;
		float y = mijlocYNod2 - mijlocYNod1;
		float lng = sqrt(x * x + y * y);
		float unghi = atan2(y, x) * 180 / (PI);

		line.setSize(Vector2f(lng, grosimeLinie));
		line.setPosition(mijlocXNod1, mijlocYNod1);
		line.setRotation(unghi);
		line.setFillColor(Color::Black);
		fereastraAplicatie.draw(line);

		float dimTriunghi = 30.0f;
		float inaltimeTriunghi = dimTriunghi * sqrt(3) / 2;
		triunghi.setPoint(0, Vector2f(0, -inaltimeTriunghi / 2));
		triunghi.setPoint(1, Vector2f(dimTriunghi, 0));
		triunghi.setPoint(2, Vector2f(0, inaltimeTriunghi / 2));
		triunghi.setFillColor(Color::Black);

		triunghi.setOrigin(15, -grosimeLinie / 2);
		triunghi.setPosition(mijlocXNod2, mijlocYNod2);
		triunghi.setRotation(unghi);
		fereastraAplicatie.draw(triunghi);
	}
}

