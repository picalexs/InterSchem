#pragma once
#include "structs.h"
#include <set>
#include <SFML/Graphics.hpp>

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

bool esteNodInArbore(Nod* nodCautat, const Nod* radacina);

bool verificareSimbolInZona(const Vector2f& pozitieMouse, const DateNod& date);

Nod* gasesteNod(Nod* nodCurent, const DateNod& date);

Nod* gasesteNodInArbore(const Arbore& A, const DateNod& date);

Nod* gasesteNodCuPozMouse(const RenderWindow& fereastraAplicatie, const Arbore& A);

Nod* gasesteNodListaCuPozMouse(const RenderWindow& fereastraAplicatie);

Nod* gasesteNodInListaArbori(const DateNod& date);

int numarNoduriDinArbore(Arbore A);

int numarNoduriDinListaArbori();

void stergereNod(Nod* N);

bool existaLinie(const std::pair<DateNod, DateNod>& linie);

bool creareLegatura(Nod*& nod1, Nod*& nod2);

void seteazaVariabila(const std::string& nume, long double valoare);

long double obtineValDupaNume(const std::string& nume);

bool esteVariabila(const std::string& token);

void atribuireConstanteCunoscute();