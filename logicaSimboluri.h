#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void logicaSimboluri(const RenderWindow& fereastraAplicatie, const VideoMode& desktop);

bool esteActivaCitireaPtAlgoritm();

void opresteCitireaPtAlgoritm();

void logicaAtribuire(Nod* N);

void logicaCitire(const Nod* N);

void logicaAfisare(Nod* N);

bool logicaDaca(Nod* N);