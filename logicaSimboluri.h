#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "functiiNod.h"
using namespace sf;

void logicaCreareSimbol(RenderWindow& window, map<Keyboard::Key, bool>& esteTastaApasata);

void logicaStergereSimbol(RenderWindow& window, bool& esteApasatStergere);
