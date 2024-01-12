#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

void logicaDelete();

bool seCitesteSalvare();

void activeazaSalvare();

void opresteSalvare();

bool seCitesteParcurgereProgram();

std::string getNumeFisierSalvare();

void activeazaParcurgereaTotala();

void logicaInput(const Event& event);

void logicaExecutareInput(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event);
