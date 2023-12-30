#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

void desenareNodStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareNodStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareNodAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareNodCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareNodAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareNodDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop, DateNod& date);

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie);

