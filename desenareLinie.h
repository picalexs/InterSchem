#pragma once
#include "functiiNod.h"

void adaugaSimbolCaObstacole(const Nod* nod);

void stergeSimbolObstacol(const Nod* nod);

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2);

void stergereLinieObstacol(const Nod* nod);

void initializareMatriceObstacole(const VideoMode& desktop);

void desenareLinii(RenderWindow& fereastraAplicatie);