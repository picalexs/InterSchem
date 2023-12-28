#pragma once
#include "structs.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void desenareNodStart(RenderWindow& window, const dateNod& date);

void desenareNodStop(RenderWindow& window,const dateNod& date);

void desenareNodAtribuire(RenderWindow& window, const dateNod& date);

void desenareNodCitire(RenderWindow& window, const dateNod& date);

void desenareNodAfisare(RenderWindow& window, const dateNod& date);

void desenareNodDaca(RenderWindow& window, const dateNod& date);

void desenareLinieIntreSimboluri(RenderWindow& window);

void mutareForma(RenderWindow& window);
