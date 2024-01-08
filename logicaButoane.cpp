#include "logicaButoane.h"
#include "butoaneMeniu.h"
#include "convertireCPlusPlus.h"
#include "desenareSimboluri.h"
using namespace sf;

/*bool verificareButon(const Vector2i& pozitieMouse, float x, float y, const VideoMode& desktop) {
	return (abs(x - pozitieMouse.x) <= desktop.width/10-desktop.width/5 && abs(y - pozitieMouse.y) <= desktop.height/15-desktop.height/5);
}*/

bool verificareButon(const sf::Vector2i& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime &&
		pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	float buttonX = 0.91f * desktop.width / 100;
	float buttonY = 0.83f * desktop.height / 100;
		sf::Vector2i pozitieMouse = sf::Mouse::getPosition(fereastraAplicatie);

			RenderWindow newWindow(sf::VideoMode(static_cast<float>(50 * desktop.width / 100), static_cast<float>(50 * desktop.height / 100)), "Ajutor");
			newWindow.setFramerateLimit(60);

			const int marimeFont = static_cast<int>(desktop.width) / 70;
			Text mainText("Proiect InterSchem\n \n Blocurile se vor muta dupa mouse, daca este apasat butonul din stanga;\n \n Pentru a crea legaturi, se vor trasa cu butonul din dreapta mouse-ului; \n \n Pentru a crea blocuri, se vor apasa tastele CTRL+1(START), CTRL+2(STOP)\n CTRL+3(ATRIBUIRE), CTRL+4(CITIRE), CTRL+5(AFISARE), \n CTRL+6(DECIZIE) sau se vor folosi butoanele din meniu;\n \n Pentru a sterge un bloc si legatura sa, se va apasa ESCAPE\n \n Pentru executarea algoritmului se va folosi F12 \n \n Butonul de salvare va salva schema logica, iar cu cel de incarcare se vor \n incarca scheme logice deja facute", fontGlobal, marimeFont);
			mainText.setFillColor(Color::White);
			mainText.setPosition(desktop.width/100, desktop.height/100);

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

void desenareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	sf::Vector2i pozitieMouse = sf::Mouse::getPosition(fereastraAplicatie);
	{
		butonStart(fereastraAplicatie, desktop);
		butonStop(fereastraAplicatie, desktop);
		butonCitire(fereastraAplicatie, desktop);
		butonAfisare(fereastraAplicatie, desktop);
		butonAtribuire(fereastraAplicatie, desktop);
		butonDaca(fereastraAplicatie, desktop);
		///butonCatTimp(fereastraAplicatie, desktop);
	}
}
void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	int lungime, inaltime;
	lungime = 60*desktop.width / 100;
	inaltime = 72*desktop.height / 100;
	sf::RectangleShape rectangle(sf::Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * desktop.width / 100, 10 * desktop.height / 100);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));
	rectangle.setFillColor(sf::Color(255,255, 255));
	fereastraAplicatie.draw(rectangle);

	butonSalvareConvertire(fereastraAplicatie, desktop);
	convertire(fereastraAplicatie, desktop);
}

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	butonRulareTotal(fereastraAplicatie, desktop);
	butonRularePas(fereastraAplicatie, desktop);
}

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	static bool esteApasatMouse = false;
	static bool esteActivatDrop = false;
	static bool esteActivatDropRulare = false, esteActivatConvertire=false;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && esteApasatMouse==false)
	{
		   esteApasatMouse = true;
	}
	if (!(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) && esteApasatMouse == true)
	{
		sf::Vector2i pozitieMouse = sf::Mouse::getPosition(fereastraAplicatie);
		esteApasatMouse = false;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, desktop.height / 100, desktop.width/10, desktop.height/15))
		{
			esteActivatDrop = !esteActivatDrop;
		}
		if (verificareButon(pozitieMouse, 89 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
			esteActivatDropRulare = !esteActivatDropRulare;

		if (verificareButon(pozitieMouse, 91 * desktop.width / 100, 83 * desktop.height / 100, desktop.width / 15, desktop.height / 15))
		    desenareAjutor(fereastraAplicatie, desktop, event);

		if (verificareButon(pozitieMouse, 78 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 15))
			esteActivatConvertire = !esteActivatConvertire;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 24 * desktop.height / 100, desktop.width / 10, desktop.height / 25))
			creareSimbolPtListaArbori(fereastraAplicatie, desktop);

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton start
			cout << 1;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton stop
			cout << 2;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 16 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton citire
			cout << 3;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 20 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton afisare
			cout << 4;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 24 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton atribuire
			cout << 5;

		if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 28 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton decizie
			cout << 6;

		if (verificareButon(pozitieMouse, desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton salvare
			cout << "salvare";

		if (verificareButon(pozitieMouse, 12 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))///buton incarcare
			cout << "incarcare";

		if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///rulare total
			cout << "rulare total";

		if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///rulare pas cu pas
			cout << "rulare pas cu pas";

		if (verificareButon(pozitieMouse, 71 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 10, desktop.height / 25))///salvare convertire
			cout << "salvare convertire";
	}
	if (esteActivatDrop)
		desenareDropDown(fereastraAplicatie, desktop, event);
	if (esteActivatConvertire)
		desenareConvertire(fereastraAplicatie, desktop, event);
	if (esteActivatDropRulare)
		desenareDropDownRulare(fereastraAplicatie, desktop, event);
}
