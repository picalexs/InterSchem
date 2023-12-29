#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void logicaSimboluri(const RenderWindow& fereastraAplicatie);

bool esteActivaCitireaPtAlgoritm();

void opresteCitireaPtAlgoritm();

void logicaAtribuire(nod* N);

void logicaCitire(const nod* N);

void logicaAfisare(nod* N);

bool logicaDaca(nod* N);