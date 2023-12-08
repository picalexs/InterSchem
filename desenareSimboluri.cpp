#include "desenareSimboluri.h"

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