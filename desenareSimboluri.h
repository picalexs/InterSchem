#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie);

void desenareOutline(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

Nod* verificareOutline(const RenderWindow& fereastraAplicatie);