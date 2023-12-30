#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void creareSimbol(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const VideoMode& desktop, Nod* N);

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop);
