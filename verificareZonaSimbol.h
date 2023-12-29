#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

bool verificareSimbolStart(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolStop(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolAtribuire(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolCitire(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolAfisare(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolDaca(Vector2i pozitieMouse, DateNod date);

bool verificareSimbolInZona(Vector2i pozitieMouse, DateNod date);