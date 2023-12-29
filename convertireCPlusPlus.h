#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void nrStartStop(Arbore A, const DateNod& date);

void verificare(Nod* nodCurent, const DateNod& date);

void parcurgere(Nod* nodCurent, const DateNod& date);