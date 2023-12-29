#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void desenareNodStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareNodStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareNodAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareNodCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareNodAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareNodDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date);

void desenareLinieIntreSimboluri(RenderWindow& fereastraAplicatie);

