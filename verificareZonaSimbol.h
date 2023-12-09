#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

bool verificareSimbolStart(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolStop(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolAtribuire(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolCitire(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolAfisare(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolDaca(Vector2i pozitieMouse, dateNod date);

bool verificareSimbolInZona(Vector2i pozitieMouse, dateNod date);