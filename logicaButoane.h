#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event);

void verificareApasare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event);

bool verificareButon(const Vector2f& pozitieMouse, float x, float y, const VideoMode& desktop);

void verificareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event);
