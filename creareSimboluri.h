#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void creareSimbol(RenderWindow& window, const dateNod& date);

void creareSimbolPtArbore(RenderWindow& window, const nod* N);

void creareSimbolPtListaArbori(RenderWindow& window);
