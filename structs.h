#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct DateNod {
	int tip = -1; //0-START, 1-STOP, 2-Atribuire, 3-Citire, 4-Afisare, 5-Daca/While
	std::string expresie;
	float x = 0, y = 0;
	float lungimeSimbol = 0, inaltimeSimbol = 0;
};

struct Nod {
	DateNod date;
	Nod* st = nullptr, * dr = nullptr;
};

struct Arbore {
	Nod* radacina = nullptr;
	int nrNoduri = 0;
};

extern vector<Arbore> listaArbori;
extern vector<pair<DateNod, DateNod>> listaLinii;
extern unordered_map<string, long double> variabile;
extern vector<string> listaConsola;
extern Font fontGlobal;
