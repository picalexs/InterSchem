#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void desenareOutline(RenderWindow& fereastraAplicatie, const DateNod& dateNod, const int marimeOutline);

Nod* verificareOutline(const RenderWindow& fereastraAplicatie);