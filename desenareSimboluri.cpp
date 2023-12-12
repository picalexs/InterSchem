#include "desenareSimboluri.h"
#include <cmath>
#define PI 3.14159265358979323846

void desenareLinie(RenderWindow& window, const dateNod& date) {
	sf::RectangleShape line(sf::Vector2f(500, 4));
	line.setPosition(date.x/2, date.y/2);
	line.setFillColor(Color::Black);
	window.draw(line);
}

void desenareDreptunghi(RenderWindow& window, const dateNod& date) {
	sf::RectangleShape rectangle(sf::Vector2f(500, 4));
	rectangle.setPosition(date.x / 2, date.y / 2);
	rectangle.setFillColor(Color::Black);
	window.draw(rectangle);
}

void desenareTriunghi(RenderWindow& window, const dateNod& date) {
	sf::CircleShape triangle;
	triangle.setRadius(75);
	triangle.setPointCount(3);
	window.draw(triangle);
	triangle.setPosition(date.x - 75, date.y);
	triangle.setFillColor(Color::Yellow);
	window.draw(triangle);
}

void desenareElipsa(RenderWindow& window, const dateNod& date, float raza_x, float raza_y, int calitate, Color culoare)
{
	sf::ConvexShape ellipse;
	ellipse.setPointCount(calitate);

	for (int i = 0; i < calitate; ++i) {
		float rad = (360 / calitate * i) / (360 / PI / 2);
		float x = cos(rad) * raza_x;
		float y = sin(rad) * raza_y;
		ellipse.setPoint(i, sf::Vector2f(x, y));
	};
	ellipse.setPosition(date.x, date.y + raza_y);
	ellipse.setFillColor(culoare);
	window.draw(ellipse);
}

void desenareNodStart(RenderWindow& window,const Font &font, const dateNod& date) {
	float raza_x = 65, raza_y = 25;
	int calitate = 10;
	Color culoare(120, 189, 219);
	desenareElipsa(window, date, raza_x, raza_y, calitate, culoare);

	Text textStart("START", font, 24);
	textStart.setFillColor(Color::Black);

	FloatRect textBounds = textStart.getLocalBounds();
	textStart.setOrigin(textBounds.left + textBounds.width / 2.0,textBounds.top + textBounds.height/2);
	textStart.setPosition(date.x, date.y + raza_y);

	window.draw(textStart);
}


void desenareNodStop(RenderWindow& window,const Font &font, const dateNod& date) {
	float raza_x = 65, raza_y = 25;
	int calitate = 10;
	Color culoare(120, 189, 219);
	desenareElipsa(window, date, raza_x, raza_y, calitate, culoare);


	Text textStart("STOP", font, 24);
	textStart.setFillColor(Color::Black);

	FloatRect textBounds = textStart.getLocalBounds();
	textStart.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + textBounds.height / 2);
	textStart.setPosition(date.x, date.y + raza_y);

	window.draw(textStart);
}

void desenareNodAtribuire(RenderWindow& window, const dateNod& date) {
	
	sf::RectangleShape rectangle(sf::Vector2f(150, 50));
	rectangle.setPosition(date.x - 75, date.y);
	rectangle.setFillColor(Color(247	,218,100));
	window.draw(rectangle);
}

void desenareNodCitire(RenderWindow& window, const dateNod& date) {
	sf::ConvexShape convex;
	convex.setPosition(date.x-100, date.y);
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(200, 0));
	convex.setPoint(2, sf::Vector2f(175, 50));
	convex.setPoint(3, sf::Vector2f(25, 50));
	convex.setFillColor(Color(148,216,150));
	window.draw(convex);
}

void desenareNodAfisare(RenderWindow& window, const dateNod& date) {
	sf::ConvexShape convex;
	convex.setPosition(date.x - 100, date.y);
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(25, 0));
	convex.setPoint(1, sf::Vector2f(175, 0));
	convex.setPoint(2, sf::Vector2f(200, 50));
	convex.setPoint(3, sf::Vector2f(0, 50));
	convex.setFillColor(Color(230, 134, 150));
	window.draw(convex);
}

void desenareNodDaca(RenderWindow& window, const dateNod& date) {
	sf::CircleShape triangle;
	triangle.setPosition(-200, -200);
	triangle.setRadius(75);
	triangle.setPointCount(3);
	window.draw(triangle);
	triangle.setPosition(date.x-75, date.y);
	triangle.setFillColor(Color(191,147,240));
	window.draw(triangle);
}

void desenareLinieIntreSimboluri(RenderWindow& window) {
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

		line.setSize(Vector2f(lng-spatiu, grosimeLinie));
		line.setPosition(mijlocXNod1, mijlocYNod1);
		line.setRotation(unghi);
		line.setFillColor(Color::Black);
		window.draw(line);

		float dimTriunghi = 30.0f;
		float inaltimeTriunghi = dimTriunghi * sqrt(3) / 2;
		triunghi.setPoint(0, sf::Vector2f(0, -inaltimeTriunghi / 2));
		triunghi.setPoint(1, sf::Vector2f(dimTriunghi, 0));
		triunghi.setPoint(2, sf::Vector2f(0, inaltimeTriunghi / 2));
		triunghi.setFillColor(sf::Color::Black);

		triunghi.setOrigin(spatiu , -grosimeLinie/2);
		triunghi.setPosition(mijlocXNod2, mijlocYNod2);
		triunghi.setRotation(unghi);
		window.draw(triunghi);
	}
}

