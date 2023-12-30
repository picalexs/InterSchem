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