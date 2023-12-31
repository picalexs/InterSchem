#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

void creareSimbol(RenderWindow& fereastraAplicatie, DateNod& date);

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, Nod* N);

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie);

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie);