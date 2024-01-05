#pragma once
#include "functiiNod.h"

void afisareMatriceObstacole();

void adaugaSimbolCaObstacole(const Nod* nod);

void stergeSimbolObstacol(const Nod* nod);

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2);

void stergereLiniiObstacoleCuNodulDat(const Nod* nod);

void actualizeazaLiniiObstacolePrinNodDat(const Nod* nod, const float valoareDeSetat);

void actualizeazaLinieObstacolPrinId(const int idLinie, const Nod* nodDeMutat);

vector<short> returneazaIduriLiniiAleNodului(const Nod* nod);

short verificareSuprapunere(const Nod* nod);

void initializareMatriceObstacole(const VideoMode& desktop);

void desenareLinii(RenderWindow& fereastraAplicatie);