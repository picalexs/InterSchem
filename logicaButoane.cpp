#include "logicaButoane.h"
#include "butoaneMeniu.h"
using namespace sf;

bool verificareButon(const Vector2i& pozitieMouse, float x, float y, const VideoMode& desktop) {
	return (abs(x - pozitieMouse.x) <= desktop.width/15 && abs(y - pozitieMouse.y) <= desktop.height/15);
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
		butonCatTimp(fereastraAplicatie, desktop);
	}
}

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	static bool esteApasatMouse = false;
	static bool esteActivatDrop = false;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && esteApasatMouse==false)
	{
		   esteApasatMouse = true;
	}
	if (!(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) && esteApasatMouse == true)
	{
		sf::Vector2i pozitieMouse = sf::Mouse::getPosition(fereastraAplicatie);
		esteApasatMouse = false;

		if (verificareButon(pozitieMouse, 500, 0, desktop))
		{
			esteActivatDrop = !esteActivatDrop;
		}
		if (verificareButon(pozitieMouse, 1240, 630, desktop))
		    desenareAjutor(fereastraAplicatie, desktop, event);
	}
	if (esteActivatDrop)
		desenareDropDown(fereastraAplicatie, desktop, event);
}
