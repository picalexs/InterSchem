#pragma once
#include "structs.h"
#include <set>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

DateNod schimbareDate(const TipNod tip, const std::string& expresie, const float x, const float y, const float lungimeSimbol, const float inaltimeSimbol);

void initializareNod(Nod& N);

void atribuireNod(Nod& N, const DateNod& date);

bool esteNodNull(const Nod* N);

Nod* creareNodNull();

Nod* creareNod(const DateNod& date);

void inserareFiu(Nod* tata, bool fiu, const DateNod& date);

void initializareArbore(Arbore& A);

void atribuireArbore(Arbore& A, const DateNod& date);

bool esteArboreNull(const Arbore& A);

bool esteRadacina(const Nod* N);

bool esteNodInArbore(const Nod* nodCautat, const Nod* radacina);

bool verificareSimbolInZona(const Vector2f& pozitieMouse, const DateNod& date);

Nod* gasesteNod(Nod* nodCurent, const DateNod& date);

Nod* gasesteNodInArbore(const Arbore& A, const DateNod& date);

Nod* gasesteNodCuPozMouse(const RenderWindow& fereastraAplicatie, const Arbore& A);

Nod* gasesteNodListaCuPozMouse(const RenderWindow& fereastraAplicatie);

Nod* gasesteNodInListaArbori(const DateNod& date);

Nod* gasesteNodTata(Nod* N, Nod*& nodCautat);

Nod* gasesteNodLegatDeWhile(Nod* nodWhile);

int pozitiaArboreleNodului(const Nod* N);

int numarNoduriMap(const Nod* N, const map<const Nod*, unsigned int>& noduriParcurse);

int numarNoduri(const Nod* N);

int numarNoduriDinArbore(Arbore A);

int numarNoduriDinListaArbori();

void stergereDinListaArbori(const Nod* N);

void stergereNod(Nod* N);

void seteazaVariabila(const std::string& nume, long double valoare);

long double obtineValDupaNume(const std::string& nume);

bool esteVariabila(const std::string& token);

void atribuireConstanteCunoscute();