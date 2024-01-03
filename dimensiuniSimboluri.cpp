#include "dimensiuniSimboluri.h"

Vector2f dimensiuniNodStart(const VideoMode& desktop)
{
	return { static_cast<float>(desktop.width / 10), static_cast<float>(desktop.height / 20) };
}

Vector2f dimensiuniNodStop(const VideoMode& desktop)
{
	return dimensiuniNodStart(desktop);
}

Vector2f dimensiuniNodAtribuire(const VideoMode& desktop)
{
	return { static_cast<float>(desktop.width / 15), static_cast<float>(desktop.height / 25) };
}

Vector2f dimensiuniNodCitire(const VideoMode& desktop)
{
	return dimensiuniNodAtribuire(desktop);
}

Vector2f dimensiuniNodAfisare(const VideoMode& desktop)
{
	return dimensiuniNodAtribuire(desktop);
}

Vector2f dimensiuniNodDaca(const VideoMode& desktop)
{
	return { static_cast<float>(desktop.width / 15 + desktop.height / 25), static_cast<float>(desktop.height / 25) };
}

Vector2f dimensiuniSimbol(const VideoMode& desktop, const int& tip)
{
	switch (tip)
	{
	case 0:
		return dimensiuniNodStart(desktop);
	case 1:
		return dimensiuniNodStop(desktop);
	case 2:
		return dimensiuniNodAtribuire(desktop);
	case 3:
		return dimensiuniNodCitire(desktop);
	case 4:
		return dimensiuniNodAfisare(desktop);
	case 5:
		return dimensiuniNodDaca(desktop);
	default:
		return { 0, 0 };
	}
}

bool modificatDimensiune = false;
void modificareLungimeSimbol(const VideoMode& desktop, DateNod& date) {
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	const Text textExpresie(date.expresie, fontGlobal, marimeFont);
	const float lungimeText = textExpresie.getLocalBounds().width;
	float spatiuMargine = 40.0f;
	if (date.tip == TipNod::DACA || date.tip == TipNod::WHILE)
		spatiuMargine = 100.0f;
	const float raport = (lungimeText + 2 * spatiuMargine) / date.lungimeSimbol;

	if (modificatDimensiune)
		date.lungimeSimbol *= raport;
	else if (raport >= 1.0f) {
		date.lungimeSimbol *= raport;
		modificatDimensiune = true;
	}
}

void reseteazaModificareDimensiune()
{
	modificatDimensiune = false;
}
