#include "desenareSimboluri.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void desenareLinie() {
	
}

void desenareDreptunghi() {

}

void desenareTriunghi() {

}

void desenareNodStart(dateNod date){
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Black);
	//desenare nod start ca elipsa folosind date.x, date.y si eventual o raza sau poate un colt st, colt dr
}

void desenareNodStop(dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Black);
	//desenare nod stop
	//acelasi lucru ca si pt nod start
}

void desenareNodAtribuire(dateNod date) {
	
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Yellow);
	//desenare nod atribuire -dreptunghi
}

void desenareNodCitire(dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Green);
	//desenare nod citire -trapez cu baza mai mare sus si baza mica jos
}

void desenareNodAfisare(dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Red);
	//desenare nod afisare -trapez cu baza mare jos, baza mica sus
}

void desenareNodDaca(dateNod date) {
	sf::CircleShape shape;
	shape.setRadius(50);
	shape.setPosition(date.x, date.y);
	shape.setFillColor(Color::Magenta);
	//desenare nod daca - triunghi
}