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
	lungimeButonStandard = desktop.width / 10;
	inaltimeButonStandard = desktop.height / 25;
	pozitieXSimbolStandard = desktop.width / 100;
	pozitieYSimbolStandard = desktop.height / 100;
}

bool verificareButonTMP(const Vector2i& pozitieMouse, float x, float y, float lungime, float inaltime) {
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

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, 14.5f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(desktop.width / 350);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);

	RectangleShape background(Vector2f(desktop.width / 14, desktop.height / 60));
	background.setFillColor(Color(110, 162, 186));
	background.setPosition(91.75f * pozitieXSimbolStandard, 15.75 * pozitieYSimbolStandard);

	RectangleShape slider(Vector2f(40.0f / (3200.0f / desktop.width), 60.0f / (2000.0f / desktop.height)));
	slider.setFillColor(culoareOutlineRulare);
	slider.setPosition(89 * pozitieXSimbolStandard, 15.0f * pozitieYSimbolStandard);

	constexpr float valMin = 0.01f;
	constexpr float valMax = 2;
	static float valoare = 0.5f;
	Vector2i pozMouse = Mouse::getPosition(fereastraAplicatie);

	if (verificareButonTMP(pozMouse, background.getPosition().x, slider.getPosition().y - slider.getSize().y / 2, background.getSize().x + slider.getSize().x / 2, slider.getSize().y)
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		pozMouse = Mouse::getPosition(fereastraAplicatie);
		float xNou = clamp(static_cast<float>(pozMouse.x), background.getPosition().x, background.getPosition().x + background.getSize().x - slider.getSize().x);
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

	Text mainText(stream.str(), fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left, marginiText.top);
	mainText.setPosition(dreptunghi.getPosition().x + desktop.width / 200, 15.75 * pozitieYSimbolStandard);

	updateazaPozSlider(slider, background, valoare, valMin, valMax);

	fereastraAplicatie.draw(mainText);
	fereastraAplicatie.draw(background);
	fereastraAplicatie.draw(slider);

	updateazaValoareVitezaDeRulare(valoare);
}

void butonSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSalvareText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	Text mainText(text, fontGlobal, static_cast<int>(desktop.width) / 70);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();

	RectangleShape rectangle(Vector2f(max(marginiText.width + 20, lungimeButonStandard), inaltimeButonStandard));
	rectangle.setPosition(pozitieXSimbolStandard, 5.5f * pozitieYSimbolStandard);
	rectangle.setFillColor(Color(255, 255, 180));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	mainText.setOrigin(marginiText.left, marginiText.top);
	mainText.setPosition(rectangle.getPosition().x, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}


void butonIncarcare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(12 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Incarcare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSelectareFisier(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text, const int nr)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(12 * pozitieXSimbolStandard, (5.5 + 4.5 * nr) * pozitieYSimbolStandard);
	rectangle.setFillColor(Color(255, 255, 180));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(text, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);

	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	mainText.setString(text);
	fereastraAplicatie.draw(mainText);
}

void desenareButoaneDeSelectatFisier(RenderWindow& fereastraAplicatie, const VideoMode& desktop, int pozScroll)
{
	const vector<string> fisiere = numeFisiereInFolder();
	constexpr int nrMaximDeFisiere = 7;
	const int startIdx = max(pozScroll, 0);
	const int stopIdx = min(static_cast<int>(fisiere.size()), pozScroll + nrMaximDeFisiere);

	for (int i = startIdx; i < stopIdx; i++)
	{
		butonSelectareFisier(fereastraAplicatie, desktop, fisiere[i], i - startIdx);
	}
}


void butonStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 5.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Start", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 10 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Stop", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 14.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Citire", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 19 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Afisare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 23.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Atribuire", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 28 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);

	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Decizie", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonCatTimp(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 33.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Cat Timp", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(78 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareRulare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Convertire C++", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSalvareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 16;
	const int inaltimeButon = desktop.height / 24;
	RectangleShape rectangle(Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(71 * pozitieXSimbolStandard, 8 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareRulare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Rularea codului", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonRulareTotal(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, 10.0f * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareExecutare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Rulare Totala", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);

	sliderVitezaRulare(fereastraAplicatie, desktop);
}

void butonRularePas(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, 5.5f * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareExecutare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Pas cu Pas", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 40;
	const int inaltimeButon = desktop.width / 40;
	RectangleShape rectangle(Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(96.5 * pozitieXSimbolStandard, 94.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare2);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("?", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}
void butonDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare2);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Instructiuni", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void desenareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonStart(fereastraAplicatie, desktop);
	butonStop(fereastraAplicatie, desktop);
	butonCitire(fereastraAplicatie, desktop);
	butonAfisare(fereastraAplicatie, desktop);
	butonAtribuire(fereastraAplicatie, desktop);
	butonDaca(fereastraAplicatie, desktop);
}

void sliderMarimeFont(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape dreptunghi(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	dreptunghi.setPosition(89 * pozitieXSimbolStandard, 8.0f * pozitieYSimbolStandard);
	dreptunghi.setFillColor(culoareExecutare);
	dreptunghi.setOutlineThickness(desktop.width / 350);
	dreptunghi.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(dreptunghi);

	RectangleShape fundal(Vector2f(desktop.width / 14, desktop.height / 60));
	fundal.setFillColor(Color(110, 162, 186));
	fundal.setPosition(91.75f * pozitieXSimbolStandard, 9.25f * pozitieYSimbolStandard);

	RectangleShape slider(Vector2f(40.0f / (3200.0f / desktop.width), 60.0f / (2000.0f / desktop.height)));
	slider.setFillColor(culoareOutlineRulare);
	slider.setPosition(89 * pozitieXSimbolStandard, 8.5f * pozitieYSimbolStandard);

	constexpr int valMin = 15;
	constexpr int valMax = 60;
	static int valoare = 50;
	Vector2i pozMouse = Mouse::getPosition(fereastraAplicatie);

	if (verificareButonTMP(pozMouse, fundal.getPosition().x, slider.getPosition().y - slider.getSize().y / 2, fundal.getSize().x + slider.getSize().x / 2, slider.getSize().y)
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		pozMouse = Mouse::getPosition(fereastraAplicatie);
		float xNou = clamp(static_cast<float>(pozMouse.x), fundal.getPosition().x, fundal.getPosition().x + fundal.getSize().x - slider.getSize().x);
		slider.setPosition(xNou, slider.getPosition().y);

		float range = valMax - valMin;
		float percentage = (xNou - fundal.getPosition().x) / (fundal.getSize().x - slider.getSize().x);
		valoare = valMin + range * percentage;
	}

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	stringstream stream;
	stream << fixed << setprecision(0) << valoare;

	Text mainText(stream.str(), fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left, marginiText.top);
	mainText.setPosition(dreptunghi.getPosition().x + desktop.width / 200, 9.5f * pozitieYSimbolStandard);

	updateMarimeFont(valoare);
	updateazaPozSlider(slider, fundal, valoare, valMin, valMax);

	fereastraAplicatie.draw(mainText);
	fereastraAplicatie.draw(fundal);
	fereastraAplicatie.draw(slider);
}

void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const int marimeFont)
{
	const int lungime = 60 * pozitieXSimbolStandard;
	const int inaltime = 92 * pozitieYSimbolStandard;
	RectangleShape rectangle(Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * pozitieXSimbolStandard, 6.5 * pozitieYSimbolStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(Color(0, 0, 0));
	rectangle.setFillColor(Color(225, 234, 247));
	fereastraAplicatie.draw(rectangle);

	const string codConvertit = getCodConvertit();
	Text mainText(codConvertit, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	mainText.setPosition(71 * desktop.width / 100, 14 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);

	sliderMarimeFont(fereastraAplicatie, desktop);
	butonSalvareConvertire(fereastraAplicatie, desktop);
}

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonRulareTotal(fereastraAplicatie, desktop);
	butonRularePas(fereastraAplicatie, desktop);
}

void desenareSalvareFereastraText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	butonSalvareText(fereastraAplicatie, desktop, text);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	float buttonX = 0.91f * pozitieXSimbolStandard;
	float buttonY = 0.83f * pozitieYSimbolStandard;
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);

	RenderWindow newWindow(VideoMode(50 * pozitieXSimbolStandard, 50 * pozitieYSimbolStandard), "Ajutor");
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
	butonSalvare(fereastraAplicatie, desktop);
	butonIncarcare(fereastraAplicatie, desktop);
	butonDropDown(fereastraAplicatie, desktop);
	butonRulare(fereastraAplicatie, desktop);
	butonConvertire(fereastraAplicatie, desktop);
}