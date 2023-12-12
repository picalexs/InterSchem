#pragma once
#include <string>
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void afisareTextNod(RenderWindow& window, nod* nodCurent);

void afisareTextLista(RenderWindow& window);

string citire(const sf::Event& event);
