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
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Black);
	window.draw(shape);
	//desenare nod start ca elipsa folosind date.x, date.y si eventual o raza sau poate un colt st, colt dr
}

void desenareNodStop(RenderWindow& window, dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Black);
	window.draw(shape);
	//desenare nod stop
	//acelasi lucru ca si pt nod start
}

void desenareNodAtribuire(RenderWindow& window, dateNod date) {
	
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Yellow);
	window.draw(shape);
	//desenare nod atribuire -dreptunghi
}

void desenareNodCitire(RenderWindow& window, dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Green);
	window.draw(shape);
	window.draw(shape);
	//desenare nod citire -trapez cu baza mai mare sus si baza mica jos
}

void desenareNodAfisare(RenderWindow& window, dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Red);
	window.draw(shape);
	//desenare nod afisare -trapez cu baza mare jos, baza mica sus
}

void desenareNodDaca(RenderWindow& window, dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x - shape.getRadius(), date.y - shape.getRadius());
	shape.setFillColor(Color::Magenta);
	window.draw(shape);
	//desenare nod daca - triunghi
}

void desenareLinieIntreSimboluri(RenderWindow& window, vector<pair<dateNod, dateNod>> listaLinii) {
	sf::RectangleShape line(sf::Vector2f(0, 5)); 

	for (auto& linie : listaLinii) {
		int mijlocXNod1 = linie.first.x;
		int mijlocYNod1 = linie.first.y;
		int mijlocXNod2 = linie.second.x;
		int mijlocYNod2 = linie.second.y;

		float x = (float)(mijlocXNod2 - mijlocXNod1);
		float y = (float)(mijlocYNod2 - mijlocYNod1);
		float lng = sqrt(x * x + y * y);
		float unghi = atan2(y, x) * 180 / (float)(PI);

		line.setSize(sf::Vector2f(lng, 5));
		line.setPosition((float)(mijlocXNod1), (float)(mijlocYNod1));
		line.setRotation(unghi);
		line.setFillColor(sf::Color::Black);

		window.draw(line);
	}
}
