#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void creareSimbol(RenderWindow& fereastraAplicatie, const dateNod& date);

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const nod* N);

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie);
