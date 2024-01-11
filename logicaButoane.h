#pragma once
#include "functiiNod.h"
#include "salvareDate.h"
#include "desenareButoaneMeniu.h"
#include "desenareSimboluri.h"
#include "executareAlgoritm.h"
#include "incarcareDate.h"
#include "logicaInput.h"
#include "logicaSimboluri.h"
#include <SFML/Graphics.hpp>

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event);

bool verificareButon(const Vector2f& pozitieMouse, float x, float y, const VideoMode& desktop);
