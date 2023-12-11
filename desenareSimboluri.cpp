#include "desenareSimboluri.h"
#include <cmath>
#define PI 3.14159265358979323846

void desenareLinie(RenderWindow& window, dateNod date) {
	sf::RectangleShape line(sf::Vector2f(500, 4));
	//line.setPosition(200, 400);
	line.setPosition(date.x/2, date.y/2);
	line.setFillColor(Color::Black);
	window.draw(line);
}

void desenareDreptunghi(RenderWindow& window, dateNod date) {
	sf::RectangleShape rectangle(sf::Vector2f(500, 4));
	rectangle.setPosition(date.x / 2, date.y / 2);
	rectangle.setFillColor(Color::Black);
	window.draw(rectangle);
}

void desenareTriunghi() {

}

void desenareNodStart(RenderWindow& window, const dateNod& date){
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Blue);
	window.draw(shape);
	//desenare nod start ca elipsa folosind date.x, date.y si eventual o raza sau poate un colt st, colt dr
}

void desenareNodStop(RenderWindow& window, const dateNod& date) {
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Blue);
	window.draw(shape);
	//desenare nod stop
	//acelasi lucru ca si pt nod start
}

void desenareNodAtribuire(RenderWindow& window, const dateNod& date) {
	
	sf::RectangleShape rectangle(sf::Vector2f(150, 50));
	rectangle.setOrigin(date.x / 2, date.y / 2);
	rectangle.setPosition(date.x - 100, date.y);
	rectangle.setFillColor(Color::Red);
	window.draw(rectangle);
	Event event;
	string s="test123  sjdjdj";
	
	Font font;
	font.loadFromFile("Arial.ttf");
	Text expresieTmp(s, font, 16);
	expresieTmp.setFillColor(sf::Color(128, 128, 0));
	expresieTmp.setRotation(90.f);
	expresieTmp.setScale(2.f, 2.f);
	expresieTmp.setPosition(rectangle.getOrigin().x, rectangle.getOrigin().y);
		while (window.pollEvent(event))
		{
			if (event.type == Event::TextEntered)
			{
				if (event.KeyPressed == Keyboard::BackSpace && s.size() != 0) {
					s.pop_back();
					window.draw(expresieTmp);
				}
				else
					if (event.text.unicode < 128)
						s.push_back((char)event.text.unicode);
				window.draw(expresieTmp);
			}
		}
	//desenare nod atribuire -dreptunghi
}

void desenareNodCitire(RenderWindow& window, dateNod date) {
	sf::ConvexShape convex;
	convex.setPosition(date.x, date.y);
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(90, 0));
	convex.setPoint(2, sf::Vector2f(75, 90));
	convex.setPoint(3, sf::Vector2f(25, 90));
	convex.setFillColor(Color::Magenta);
	window.draw(convex);
	//desenare nod citire -trapez cu baza mai mare sus si baza mica jos
}

void desenareNodAfisare(RenderWindow& window, dateNod date) {
	sf::ConvexShape convex;
	convex.setPosition(date.x, date.y);
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(90, 0));
	convex.setPoint(2, sf::Vector2f(75, 90));
	convex.setPoint(3, sf::Vector2f(25, 90));
	convex.setFillColor(Color::Green);
	window.draw(convex);
	//desenare nod afisare -trapez cu baza mare jos, baza mica sus
}

void desenareNodDaca(RenderWindow& window, dateNod date) {
	sf::CircleShape triangle;
	triangle.setRadius(75);
	triangle.setPointCount(3);
	window.draw(triangle);
	triangle.setPosition(date.x-50, date.y);
	triangle.setFillColor(Color::Yellow);
	window.draw(triangle);
	//desenare nod daca - triunghi
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

