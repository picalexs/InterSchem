#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

void creareSimbol(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const VideoMode& desktop, Nod* N);

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie);