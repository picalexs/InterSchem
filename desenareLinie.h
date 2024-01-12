#pragma once
#include <set>
#include "functiiNod.h"

void afisareMatrice();

void resetMatrice();

unsigned getIdLinie();

int existaLinie(Nod* nodStart, Nod* nodStop);

vector<int> existaLinieCuNodStop(Nod* nodStop);

vector<Nod*> toateLiniileCuNodStop(Nod*& nodStop);

vector<Nod*> toateLiniileCuNodStart(Nod*& nodStart);

void reseteazaCuloareLinii();

void adaugaSimbolCaObstacole(const Nod* nod);

void stergeSimbolObstacol(const Nod* nod);

void adaugaLinieObstacol(const Nod* nod1, const Nod* nod2, const bool linieSpreWhile, const vector<int>& poateTrecePrinIdLinii);

void actualizeazaLinieObstacolPrinId(const int idLinie, const Nod* nodDeMutat, const vector<int>& poateTrecePrinIdLinii);

void stergereLiniiObstacoleCuNodulDat(const Nod* nod);

Nod* gasesteNodObstacolInLista(Nod*& nodCurent);

void verificareSuprapunere(set<int>& obiecteSuprapuse, const Nod* nod);

void initializareMatriceObstacole(const VideoMode& desktop);

void desenareLinii(RenderWindow& fereastraAplicatie, const VideoMode& desktop);