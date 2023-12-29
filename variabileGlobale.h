#pragma once
#include "structs.h"
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <optional>
using namespace std;
using namespace sf;

extern vector<Arbore> listaArbori;
extern vector<pair<DateNod, DateNod>> listaLinii;
extern unordered_map<string, long double> variabile;
extern vector<string> listaConsola;
extern Font fontGlobal;
