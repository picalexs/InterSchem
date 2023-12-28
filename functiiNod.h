#pragma once
#include "variabileGlobale.h"
#include <unordered_set>
#include "structs.h"
#include <SFML/Graphics.hpp>

dateNod schimbareDate(int tip, const std::string& expresie, int x, int y);

void initializareNod(nod& N);

void atribuireNod(nod& N, const dateNod& date);

bool esteNodNull(const nod* N);

nod* creareNodNull();

nod* creareNod(const dateNod& date);

void inserareFiu(nod* tata, bool fiu, const dateNod& date);

void initializareArbore(arbore& A);

void atribuireArbore(arbore& A, const dateNod& date);

bool esteArboreNull(const arbore& A);

bool esteNodInArbore(nod* nodCautat, const nod* radacina);

nod* gasesteNodRecursiv(nod* nodCurent, const dateNod& date);

nod* gasesteNodInArbore(const arbore& A, const dateNod& date);

nod* gasesteNodCuPozMouse(const sf::RenderWindow& window, const arbore& A);

nod* gasesteNodListaCuPozMouse(const sf::RenderWindow& window);

nod* gasesteNodInListaArbori(const dateNod& date);

long long numarNoduri(const nod* N);

int numarNoduriDinArbore(arbore A);

int numarNoduriDinListaArbori();

void stergereDinListaArbori(const nod* N);

void stergereIntregArbore(nod*& N);

void stergereArboreCuRadacina(arbore& A);

void stergereNodFaraSubarbore(arbore& A, nod* N);

bool existaLinie(const std::pair<dateNod, dateNod>& linie);

bool creareLegatura(nod*& nod1, nod*& nod2);

void seteazaVariabila(const std::string& nume, long double valoare);

long double obtineValDupaNume(const std::string& nume);

bool esteVariabila(const std::string& token);

void atribuireConstanteCunoscute();