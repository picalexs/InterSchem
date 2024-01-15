#pragma once
#include "functiiNod.h"
#include <SFML/Graphics.hpp>

void setDimensiuniStandard(const VideoMode& desktop);

void desenareButoaneDeSelectatFisier(RenderWindow& fereastraAplicati, const int pozScroll);

void desenareDropDown(RenderWindow& fereastraAplicatie);

void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const int marimeFont);

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void desenareSalvareFereastraText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text);

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop);

void butoaneMeniu(RenderWindow& fereastraAplicatie, const VideoMode& desktop);
