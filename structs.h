#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

enum class TipNod
{
	START = 0,
	STOP = 1,
	ATRIBUIRE = 2,
	CITIRE = 3,
	AFISARE = 4,
	DACA = 5,
	WHILE = 6,
	NEDEFINIT = 7
};

struct DateNod {
	TipNod tip;
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
