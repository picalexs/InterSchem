#include "logicaButoane.h"

bool esteApasatButon = false;
bool esteRidicatButon = false;

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		esteApasatButon = true;
	}
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		esteRidicatButon = true;
	}
}

void verificareApasare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	if (esteApasatButon == true)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(fereastraAplicatie);
		sf::Vector2f worldMousePos = fereastraAplicatie.mapPixelToCoords(mousePosition);
		if (worldMousePos.x >= 25 && worldMousePos.y <= 650 && worldMousePos.x <= desktop.width / 15 && worldMousePos.y >= desktop.height / 15)
			cout << 1;
	}
}
