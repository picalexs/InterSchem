#include "logicaButoane.h"
#include "butoaneMeniu.h"
#include "convertireCPlusPlus.h"
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
		///sf::Vector2f worldMousePos = fereastraAplicatie.mapPixelToCoords(mousePosition);
			RenderWindow newWindow(sf::VideoMode(400, 300), "New Window");
			newWindow.setFramerateLimit(60);

			const int marimeFont = static_cast<int>(desktop.width) / 70;
			Text mainText("Bla Bla", fontGlobal, marimeFont);
			mainText.setFillColor(Color::White);
			const FloatRect marginiText = mainText.getLocalBounds();
			mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
			mainText.setPosition(100, 100);

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
	///sf::Vector2f worldMousePos = fereastraAplicatie.mapPixelToCoords(mousePosition);
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
	inaltime = 40*desktop.height / 100;
	sf::RectangleShape rectangle(sf::Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * desktop.width / 100, 30 * desktop.height / 100);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));
	rectangle.setFillColor(sf::Color(255,255, 255));
	fereastraAplicatie.draw(rectangle);
	///convertire(fereastraAplicatie, desktop);
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
	}
	if (esteActivatDrop)
		desenareDropDown(fereastraAplicatie, desktop, event);
	if (esteActivatDropRulare)
		desenareDropDownRulare(fereastraAplicatie, desktop, event);
	if (esteActivatConvertire)
		desenareConvertire(fereastraAplicatie, desktop, event);
}
