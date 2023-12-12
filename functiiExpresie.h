#pragma once
#include <string>
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void afisareTextNod(RenderWindow& window,const Font &font, const nod* nodCurent);

void afisareTextLista(RenderWindow& window,const Font &font);

string citire(const sf::Event& event);
