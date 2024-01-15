#include "desenareButoaneMeniu.h"
#include <iomanip>
#include <sstream>
#include "convertireCPlusPlus.h"
#include "executareAlgoritm.h"
#include "incarcareDate.h"
#include "logicaButoane.h"

float lungimeButonStandard = 0;
float inaltimeButonStandard = 0;
float pozitieXSimbolStandard = 0;
float pozitieYSimbolStandard = 0;
float grosimeOutline = 0;
int marimeFontStandard = 0;
Color culoareTextStandard(0, 0, 0);
Color culoareOutlineStandard(232, 157, 51);
Color culoareOutlineCreare(145, 15, 40);
Color culoareOutlineCreareSimboluri(212, 42, 75);
Color culoareOutlineRulare(24, 117, 158);
Color culoareOutlineExecutare(33, 138, 184);
Color culoareCreare1(235, 100, 128);
Color culoareCreare2(232, 77, 108);
Color culoareRulare(119, 196, 230);
Color culoareExecutare(161, 208, 230);
Color culoareStandard(255, 217, 106);

void setDimensiuniStandard(const VideoMode& desktop)
{
	lungimeButonStandard = static_cast<float>(desktop.width) / 10.0f;
	inaltimeButonStandard = static_cast<float>(desktop.height) / 25.0f;
	pozitieXSimbolStandard = static_cast<float>(desktop.width) / 100.0f;
	pozitieYSimbolStandard = static_cast<float>(desktop.height) / 100.0f;
	grosimeOutline = static_cast<float>(desktop.width) / 350.0f;
	marimeFontStandard = static_cast<int>(desktop.width) / 70;
}

bool verificareButonTMP(const Vector2f& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime && pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

int clamp(float value, float minim, float maxim) {
	return max(minim, min(value, maxim));
}

void updateazaPozSlider(RectangleShape& slider, const RectangleShape& fundalSlider, float valoare, float minim, float maxim) {
	const float interval = maxim - minim;
	const float procentaj = (valoare - minim) / interval;
	const float sliderX = fundalSlider.getPosition().x + (fundalSlider.getSize().x - slider.getSize().x) * procentaj;
	slider.setPosition(sliderX, slider.getPosition().y);
}

void sliderVitezaRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89.0f * pozitieXSimbolStandard, 14.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);

	RectangleShape background(Vector2f(static_cast<float>(desktop.width) / 14.0f, static_cast<float>(desktop.height) / 60.0f));
	background.setFillColor(Color(110, 162, 186));
	background.setPosition(91.75f * pozitieXSimbolStandard, 15.75f * pozitieYSimbolStandard);

	RectangleShape slider(Vector2f(40.0f / (3200.0f / static_cast<float>(desktop.width)), 60.0f / (2000.0f / static_cast<float>(desktop.height))));
	slider.setFillColor(culoareOutlineRulare);
	slider.setPosition(89 * pozitieXSimbolStandard, 15.0f * pozitieYSimbolStandard);

	constexpr float valMin = 0.01f;
	constexpr float valMax = 2;
	static float valoare = 0.5f;
	const Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
	const Vector2f pozitieMouseWorld = fereastraAplicatie.mapPixelToCoords(pozitieMouse);

	if (verificareButonTMP(pozitieMouseWorld, background.getPosition().x, slider.getPosition().y - slider.getSize().y / 2, background.getSize().x + slider.getSize().x / 2, slider.getSize().y)
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		float xNou = clamp(pozitieMouseWorld.x, background.getPosition().x, background.getPosition().x + background.getSize().x - slider.getSize().x);
		slider.setPosition(xNou, slider.getPosition().y);

		float range = valMax - valMin;
		float percentage = (xNou - background.getPosition().x) / (background.getSize().x - slider.getSize().x);
		valoare = valMin + range * percentage;
	}

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	stringstream stream;
	if (valoare < 0.01f) {
		stream << fixed << setprecision(1) << valoare;
	}
	else {
		stream << fixed << setprecision(2) << valoare;
	}

	Text textButon(stream.str(), fontGlobal, marimeFont);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left, marginiText.top);
	textButon.setPosition(dreptunghi.getPosition().x + static_cast<float>(desktop.width) / 200.0f, 15.75f * pozitieYSimbolStandard);

	updateazaPozSlider(slider, background, valoare, valMin, valMax);

	fereastraAplicatie.draw(textButon);
	fereastraAplicatie.draw(background);
	fereastraAplicatie.draw(slider);

	updateazaValoareVitezaDeRulare(valoare);
}

void butonSalvare(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(pozitieXSimbolStandard, pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareStandard);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Salvare", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonSalvareText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	Text textButon(text, fontGlobal, static_cast<int>(desktop.width) / 70);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();

	RectangleShape dreptunghi(Vector2f(max(marginiText.width + 20, lungimeButonStandard), inaltimeButonStandard));
	dreptunghi.setPosition(pozitieXSimbolStandard, 5.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(Color(255, 255, 180));
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(dreptunghi);

	textButon.setOrigin(marginiText.left, marginiText.top);
	textButon.setPosition(dreptunghi.getPosition().x, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}


void butonIncarcare(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(12 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareStandard);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Incarcare", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonSelectareFisier(RenderWindow& fereastraAplicatie, const string& text, const int nr)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(12 * pozitieXSimbolStandard, (5.5f + 4.5f * static_cast<float>(nr)) * pozitieYSimbolStandard);
	dreptunghi.setFillColor(Color(255, 255, 180));
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon(text, fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);

	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	textButon.setString(text);
	fereastraAplicatie.draw(textButon);
}

void desenareButoaneDeSelectatFisier(RenderWindow& fereastraAplicatie,const int pozScroll)
{
	const vector<string> fisiere = numeFisiereInFolder();
	constexpr int nrMaximDeFisiere = 7;
	const int startIdx = max(pozScroll, 0);
	const int stopIdx = min(static_cast<int>(fisiere.size()), pozScroll + nrMaximDeFisiere);

	for (int i = startIdx; i < stopIdx; i++)
	{
		butonSelectareFisier(fereastraAplicatie, fisiere[i], i - startIdx);
	}
}

void butonStart(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 5.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Start", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonStop(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 10 * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Stop", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonCitire(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 14.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Citire", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonAfisare(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 19 * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Afisare", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonAtribuire(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 23.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Atribuire", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonDaca(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 28 * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);

	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Decizie", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonCatTimp(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, 33.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare1);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Cat Timp", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonConvertire(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(78 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareRulare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Convertire C++", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonSalvareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const float lungimeButon = static_cast<float>(desktop.width) / 16.0f;
	const float inaltimeButon = static_cast<float>(desktop.height) / 24.0f;
	RectangleShape dreptunghi(Vector2f(lungimeButon, inaltimeButon));

	dreptunghi.setPosition(71 * pozitieXSimbolStandard, 8 * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareStandard);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Salvare", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonRulare(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareRulare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Rularea codului", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonRulareTotal(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, 10.0f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);


	Text textButon("Rulare Totala", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);

	sliderVitezaRulare(fereastraAplicatie, desktop);
}

void butonRularePas(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, 5.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);


	Text textButon("Pas cu Pas", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void butonAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const float lungimeButon = static_cast<float>(desktop.width) / 40.0f;
	const float inaltimeButon = static_cast<float>(desktop.width) / 40.0f;
	RectangleShape dreptunghi(Vector2f(lungimeButon, inaltimeButon));

	dreptunghi.setPosition(96.5f * pozitieXSimbolStandard, 94.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare2);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("?", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}
void butonDropDown(RenderWindow& fereastraAplicatie)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(23 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareCreare2);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(dreptunghi);

	Text textButon("Instructiuni", fontGlobal, marimeFontStandard);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	textButon.setPosition(dreptunghi.getPosition().x + dreptunghi.getSize().x / 2, dreptunghi.getPosition().y + dreptunghi.getSize().y / 2);
	fereastraAplicatie.draw(textButon);
}

void desenareDropDown(RenderWindow& fereastraAplicatie)
{
	butonStart(fereastraAplicatie);
	butonStop(fereastraAplicatie);
	butonCitire(fereastraAplicatie);
	butonAfisare(fereastraAplicatie);
	butonAtribuire(fereastraAplicatie);
	butonDaca(fereastraAplicatie);
}

void slidermarimeFontStandard(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, 8.0f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);

	RectangleShape fundal(Vector2f(static_cast<float>(desktop.width) / 14.0f, static_cast<float>(desktop.height) / 60.0f));
	fundal.setFillColor(Color(110, 162, 186));
	fundal.setPosition(91.75f * pozitieXSimbolStandard, 9.25f * pozitieYSimbolStandard);

	RectangleShape slider(Vector2f(40.0f / (3200.0f / static_cast<float>(desktop.width)), 60.0f / (2000.0f / static_cast<float>(desktop.height))));
	slider.setFillColor(culoareOutlineRulare);
	slider.setPosition(89 * pozitieXSimbolStandard, 8.5f * pozitieYSimbolStandard);

	constexpr int valMin = 15;
	constexpr int valMax = 60;
	static int valoare = 50;
	const Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
	const Vector2f pozitieMouseWorld = fereastraAplicatie.mapPixelToCoords(pozitieMouse);

	if (verificareButonTMP(pozitieMouseWorld, fundal.getPosition().x, slider.getPosition().y - slider.getSize().y / 2, fundal.getSize().x + slider.getSize().x / 2, slider.getSize().y)
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		float xNou = clamp(pozitieMouseWorld.x, fundal.getPosition().x, fundal.getPosition().x + fundal.getSize().x - slider.getSize().x);
		slider.setPosition(xNou, slider.getPosition().y);

		float range = valMax - valMin;
		float percentage = (xNou - fundal.getPosition().x) / (fundal.getSize().x - slider.getSize().x);
		valoare = valMin + static_cast<int>(range * percentage);
	}

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	stringstream stream;
	stream << fixed << setprecision(0) << valoare;

	Text textButon(stream.str(), fontGlobal, marimeFont);
	textButon.setFillColor(culoareTextStandard);
	const FloatRect marginiText = textButon.getLocalBounds();
	textButon.setOrigin(marginiText.left, marginiText.top);
	textButon.setPosition(dreptunghi.getPosition().x + static_cast<float>(desktop.width) / 200.0f, 9.5f * pozitieYSimbolStandard);

	updateMarimeFont(valoare);
	updateazaPozSlider(slider, fundal, valoare, valMin, valMax);

	fereastraAplicatie.draw(textButon);
	fereastraAplicatie.draw(fundal);
	fereastraAplicatie.draw(slider);
}

void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const int marimeFont)
{
	const float lungime = 60.0f * pozitieXSimbolStandard;
	const float inaltime = 92.0f * pozitieYSimbolStandard;
	RectangleShape dreptunghi(Vector2f(lungime, inaltime));

	dreptunghi.setPosition(70 * pozitieXSimbolStandard, 6.5f * pozitieYSimbolStandard);
	dreptunghi.setOutlineThickness(grosimeOutline);
	dreptunghi.setOutlineColor(Color(0, 0, 0));
	dreptunghi.setFillColor(Color(225, 234, 247));
	fereastraAplicatie.draw(dreptunghi);

	const string codConvertit = getCodConvertit();
	Text textButon(codConvertit, fontGlobal, marimeFont);
	textButon.setFillColor(culoareTextStandard);
	textButon.setPosition(71 * pozitieXSimbolStandard, 14 * pozitieYSimbolStandard);
	fereastraAplicatie.draw(textButon);

	slidermarimeFontStandard(fereastraAplicatie, desktop);
	butonSalvareConvertire(fereastraAplicatie, desktop);
}

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonRulareTotal(fereastraAplicatie, desktop);
	butonRularePas(fereastraAplicatie);
}

void desenareSalvareFereastraText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	butonSalvareText(fereastraAplicatie, desktop, text);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	float buttonX = 0.91f * pozitieXSimbolStandard;
	float buttonY = 0.83f * pozitieYSimbolStandard;

	RenderWindow newWindow(VideoMode(static_cast<int>(50 * pozitieXSimbolStandard), static_cast <int>(50 * pozitieYSimbolStandard)), "Ajutor");
	newWindow.setFramerateLimit(10);

	Texture texture;
	if (!texture.loadFromFile("ajutor.jpg"))
	{
		cout << "Nu s-a putut incarca imaginea!!" << endl;
		return;
	}

	Sprite sprite(texture);
	sprite.setScale(Vector2f(newWindow.getSize().x / static_cast<float>(texture.getSize().x), newWindow.getSize().y / static_cast<float>(texture.getSize().y)));
	newWindow.draw(sprite);
	newWindow.display();

	while (newWindow.isOpen())
	{
		Event event;
		while (newWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				newWindow.close();
			}
		}
	}
}

void butoaneMeniu(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonAjutor(fereastraAplicatie, desktop);
	butonSalvare(fereastraAplicatie);
	butonIncarcare(fereastraAplicatie);
	butonDropDown(fereastraAplicatie);
	butonRulare(fereastraAplicatie);
	butonConvertire(fereastraAplicatie);
}