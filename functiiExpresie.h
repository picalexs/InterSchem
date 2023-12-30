#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
using namespace sf;

void afisareTextLista(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void functieDebugging(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void afisareListaOutput(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void stergereSpatii(string& expresie);