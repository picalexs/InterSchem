#pragma once
#include <set>

#include "functiiNod.h"

unsigned short getIdLinie();

void afisareMatriceObstacole();

void adaugaSimbolCaObstacole(const Nod* nod);

void stergeSimbolObstacol(const Nod* nod);

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2, const bool linieSpreWhile);

void actualizeazaLinieObstacolPrinId(const int idLinie, const Nod* nodDeMutat);

void stergereLiniiObstacoleCuNodulDat(const Nod* nod);

Nod* gasesteNodObstacolInLista(Nod*& nodCurent);

set<short> verificareSuprapunere(const Nod* nod);

void initializareMatriceObstacole(const VideoMode& desktop);

void desenareLinii(RenderWindow& fereastraAplicatie);