#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void logicaCreareSimbol(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const int tip);

void logicaStergereSimbol(const RenderWindow& fereastraAplicatie);

void logicaGasireNoduriDeLegat(const RenderWindow& fereastraAplicatie);

void logicaLegaturaIntreSimboluri(bool esteLegaturaIncarcat);

void adaugaLinie(Nod*& nodStart, Nod*& nodStop);