#pragma once
#include <SFML/Graphics.hpp>
#include "functiiNod.h"
using namespace sf;

void logicaCreareSimbol(const RenderWindow& window);

void logicaStergereSimbol(const RenderWindow& window);

void logicaLegaturaIntreSimboluri(const RenderWindow& window);

void logicaSimboluri(const RenderWindow& window);

bool esteActivaCitireaPtAlgoritm();

void opresteCitireaPtAlgoritm();

void logicaAtribuire(nod* N);

void logicaCitire(const nod* N);

void logicaAfisare(nod* N);

bool logicaDaca(nod* N);