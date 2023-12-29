#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void creareSimbol(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Nod* N);

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop);
