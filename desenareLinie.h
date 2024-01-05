#pragma once
#include "functiiNod.h"

void afisareMatriceObstacole();

void adaugaSimbolCaObstacole(const Nod* nod);

void stergeSimbolObstacol(const Nod* nod);

void creeazaSpatiuJosPtLinieInSimbol(const Nod* nod);

void creeazaSpatiuSusPtLinieInSimbol(const Nod* nod);

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2);

void stergereLiniiObstacoleCuNodulDat(const Nod* nod);

void actualizeazaLinieObstacolPrinId(const int idLinie, const Nod* nodDeMutat);

Nod* gasesteNodObstacolInLista(Nod*& nodCurent);

short verificareSuprapunere(const Nod* nod);

void initializareMatriceObstacole(const VideoMode& desktop);

void desenareLinii(RenderWindow& fereastraAplicatie);