#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
using namespace sf;

bool nrStartStop(int& nrStart, int& nrStop, const Nod* NodCurent);

bool verificare(Nod* nodCurent, const DateNod& date);

void parcurgere(Nod* nodCurent);

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop);