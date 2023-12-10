#include "desenareSimboluri.h"
#include <cmath>
#define PI 3.14159265358979323846

void desenareLinie() {
	
}

void desenareDreptunghi() {

}

void desenareTriunghi() {

}

void desenareNodStart(RenderWindow& window, dateNod date){
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Blue);
	window.draw(shape);
	//desenare nod start ca elipsa folosind date.x, date.y si eventual o raza sau poate un colt st, colt dr
}

void desenareNodStop(RenderWindow& window, dateNod date) {
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Blue);
	window.draw(shape);
	//desenare nod stop
	//acelasi lucru ca si pt nod start
}

void desenareNodAtribuire(RenderWindow& window, dateNod date) {
	
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Yellow);
	window.draw(shape);
	//desenare nod atribuire -dreptunghi
}

void desenareNodCitire(RenderWindow& window, dateNod date) {
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Green);
	window.draw(shape);
	window.draw(shape);
	//desenare nod citire -trapez cu baza mai mare sus si baza mica jos
}

void desenareNodAfisare(RenderWindow& window, dateNod date) {
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Red);
	window.draw(shape);
	//desenare nod afisare -trapez cu baza mare jos, baza mica sus
}

void desenareNodDaca(RenderWindow& window, dateNod date) {
	CircleShape shape;
	shape.setRadius(30);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Magenta);
	window.draw(shape);
	//desenare nod daca - triunghi
}

void desenareLinieIntreSimboluri(RenderWindow& window) {
	float grosimeLinie = 5;
	float spatiu = 55;
	RectangleShape line(Vector2f(0, grosimeLinie));
	ConvexShape triunghi(3);

	for (auto& linie : listaLinii) {
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

