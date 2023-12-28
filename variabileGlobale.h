#pragma once
#include "structs.h"
#include <vector>
#include <unordered_map>
#include <SFML/Graphics/Font.hpp>
using namespace std;

extern vector<arbore> listaArbori;
extern vector<pair<dateNod, dateNod>> listaLinii;
extern unordered_map<string, long double> variabile;
extern vector<string> listaConsola;
extern sf::Font fontGlobal;