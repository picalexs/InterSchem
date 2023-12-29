#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void nrStartStop(arbore A, const dateNod& date);

void verificare(nod* nodCurent, const dateNod& date);

void parcurgere(nod* nodCurent, const dateNod& date);