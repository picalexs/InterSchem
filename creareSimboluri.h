#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void creareSimbol(RenderWindow& window, const Font& font, const dateNod& date);

void creareSimbolPtArbore(RenderWindow& window, const Font& font, const nod* N);

void creareSimbolPtListaArbori(RenderWindow& window, const Font& font);
