#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Vector2f dimensiuneSimbol(const VideoMode& desktop, const int& tip);

void modificareLungimeSimbol(const VideoMode& desktop, DateNod& date);

void reseteazaModificareDimensiune();