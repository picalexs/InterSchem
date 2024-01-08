#include "logicaButoane.h"
#include "butoaneMeniu.h"
#include "convertireCPlusPlus.h"
#include "desenareSimboluri.h"
#include "executareAlgoritm.h"
#include "incarcareDate.h"
#include "logicaSimboluri.h"
#include "salvareDate.h"
using namespace sf;

bool verificareButon(const Vector2i& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime && pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	float buttonX = 0.91f * desktop.width / 100;
	float buttonY = 0.83f * desktop.height / 100;
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);

	RenderWindow newWindow(VideoMode(static_cast<float>(50 * desktop.width / 100), static_cast<float>(50 * desktop.height / 100)), "Ajutor");
	newWindow.setFramerateLimit(60);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Proiect InterSchem\n \n Blocurile se vor muta dupa mouse, daca este apasat butonul din stanga;\n \n Pentru a crea legaturi, se vor trasa cu butonul din dreapta mouse-ului; \n \n Pentru a crea blocuri, se vor apasa tastele CTRL+1(START), CTRL+2(STOP)\n CTRL+3(ATRIBUIRE), CTRL+4(CITIRE), CTRL+5(AFISARE), \n CTRL+6(DECIZIE) sau se vor folosi butoanele din meniu;\n \n Pentru a sterge un bloc si legatura sa, se va apasa ESCAPE\n \n Pentru executarea algoritmului se va folosi F12 \n \n Butonul de salvare va salva schema logica, iar cu cel de incarcare se vor \n incarca scheme logice deja facute", fontGlobal, marimeFont);
	mainText.setFillColor(Color::White);
	mainText.setPosition(desktop.width / 100, desktop.height / 100);

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
		newWindow.clear(Color::Black);
		newWindow.draw(mainText);
		newWindow.display();
	}
}

void desenareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
	{
		butonStart(fereastraAplicatie, desktop);
		butonStop(fereastraAplicatie, desktop);
		butonCitire(fereastraAplicatie, desktop);
		butonAfisare(fereastraAplicatie, desktop);
		butonAtribuire(fereastraAplicatie, desktop);
		butonDaca(fereastraAplicatie, desktop);
	}
}
void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungime = 60 * desktop.width / 100;
	const int inaltime = 72 * desktop.height / 100;
	RectangleShape rectangle(Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * desktop.width / 100, 10 * desktop.height / 100);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(Color(0, 0, 0));
	rectangle.setFillColor(Color(255, 255, 255));
	fereastraAplicatie.draw(rectangle);

	butonSalvareConvertire(fereastraAplicatie, desktop);
	convertire(fereastraAplicatie, desktop);
}

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonRulareTotal(fereastraAplicatie, desktop);
	butonRularePas(fereastraAplicatie, desktop);
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
		logicaCreareSimbol(fereastraAplicatie, desktop, 2);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 20 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton afisare
		logicaCreareSimbol(fereastraAplicatie, desktop, 3);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 24 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton atribuire
		logicaCreareSimbol(fereastraAplicatie, desktop, 4);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 28 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton decizie
		logicaCreareSimbol(fereastraAplicatie, desktop, 5);
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

		logicaButoaneCreareSimboluri(fereastraAplicatie, pozitieMouse, desktop);

		if (verificareButon(pozitieMouse, desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			salvareDate();
			cout << "Apasat Buton Salvare!\n";
		}
		else if (verificareButon(pozitieMouse, 12 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			incarcareDate();
			cout << "Apasat Buton Incarcare!\n";
		}
		else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			cout << "Apasat Buton Rulare Totala!\n";
		}
		else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			executareAlgoritmPasCuPas();
			cout << "Apasat Buton Rulare Pas cu Pas!\n";
		}
		else if (verificareButon(pozitieMouse, 71 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			salvareCodConvertit();
			cout << "Apasat Buton Salvare Convertire!\n";
		}
		else if (esteActivatDrop || verificareButon(pozitieMouse, 23 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
		{
			esteActivatDrop = !esteActivatDrop;
		}
		else if (esteActivatDropRulare || verificareButon(pozitieMouse, 89 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15)) {
			esteActivatDropRulare = !esteActivatDropRulare;
		}
		else if (verificareButon(pozitieMouse, 91 * desktop.width / 100, 83 * desktop.height / 100, desktop.width / 15, desktop.height / 15)) {
			desenareAjutor(fereastraAplicatie, desktop);
		}
		else if (verificareButon(pozitieMouse, 78 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15)) {
			esteActivatConvertire = !esteActivatConvertire;
		}
		else if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 24 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
			creareSimbolPtListaArbori(fereastraAplicatie, desktop);
		}
	}
	if (esteActivatDrop) {
		desenareDropDown(fereastraAplicatie, desktop);
	}
	if (esteActivatConvertire) {
		desenareConvertire(fereastraAplicatie, desktop);
	}
	if (esteActivatDropRulare) {
		desenareDropDownRulare(fereastraAplicatie, desktop);
	}
}
