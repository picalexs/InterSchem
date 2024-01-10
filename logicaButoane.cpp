#include "logicaButoane.h"
#include "desenareButoaneMeniu.h"
#include "desenareSimboluri.h"
#include "executareAlgoritm.h"
#include "incarcareDate.h"
#include "logicaSimboluri.h"
#include "salvareDate.h"
using namespace sf;

bool verificareButon(const Vector2i& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime && pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

void logicaButoaneCreareSimboluri(const RenderWindow& fereastraAplicatie, const Vector2i pozitieMouse, const VideoMode& desktop)
{
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton start
		logicaCreareSimbol(fereastraAplicatie, desktop, 0);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton stop
		logicaCreareSimbol(fereastraAplicatie, desktop, 1);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 16 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton citire
		logicaCreareSimbol(fereastraAplicatie, desktop, 3);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 20 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton afisare
		logicaCreareSimbol(fereastraAplicatie, desktop, 4);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 24 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton atribuire
		logicaCreareSimbol(fereastraAplicatie, desktop, 2);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 28 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton decizie
		logicaCreareSimbol(fereastraAplicatie, desktop, 5);
	}
}

void logicaButoaneRulare(const Vector2i pozitieMouse, VideoMode desktop)
{
	if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		cout << "Apasat Buton Rulare Totala!\n";
	}
	else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		executareAlgoritmPasCuPas();
		cout << "Apasat Buton Rulare Pas cu Pas!\n";
	}
}

void logicaFisiere(const Vector2i pozitieMouse, VideoMode desktop)
{
	if (verificareButon(pozitieMouse, desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		salvareDate();
		cout << "Apasat Buton Salvare!\n";
	}
	else if (verificareButon(pozitieMouse, 12 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		incarcareDate();
		cout << "Apasat Buton Incarcare!\n";
	}
	if (verificareButon(pozitieMouse, 71 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		salvareCodConvertit();
		cout << "Apasat Buton Salvare Convertire!\n";
	}
}

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	static bool esteApasatMouse = false;
	static bool esteActivatDrop = false;
	static bool esteActivatDropRulare = false;
	static bool esteActivatConvertire = false;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && esteApasatMouse == false)
	{
		esteApasatMouse = true;
	}
	if (!(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) && esteApasatMouse == true)
	{
		const Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
		esteApasatMouse = false;
		if (esteActivatDrop) {
			logicaButoaneCreareSimboluri(fereastraAplicatie, pozitieMouse, desktop);
		}
		if (esteActivatDropRulare)
		{
			logicaButoaneRulare(pozitieMouse, desktop);
		}
		logicaFisiere(pozitieMouse, desktop);

		if (esteActivatDrop || verificareButon(pozitieMouse, 23 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
		{//meniu creare simboluri
			esteActivatDrop = !esteActivatDrop;
		}
		else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
		{//meniu rulare
			esteActivatDropRulare = !esteActivatDropRulare;
		}
		else if (verificareButon(pozitieMouse, 96 * desktop.width / 100, 87 * desktop.height / 100, desktop.width / 40, desktop.width / 40))
		{//buton ajutor
			desenareAjutor(fereastraAplicatie, desktop);
		}
		else if (verificareButon(pozitieMouse, 78 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
		{//buton convertire
			esteActivatConvertire = !esteActivatConvertire;
		}
	}
	if (esteActivatDrop) {
		desenareDropDown(fereastraAplicatie, desktop);
	}
	if (esteActivatConvertire) {
		desenareConvertire(fereastraAplicatie, desktop);
		convertire(fereastraAplicatie, desktop);
	}
	if (esteActivatDropRulare) {
		desenareDropDownRulare(fereastraAplicatie, desktop);
	}
}
