#include "functiiExpresie.h"

void afisareTextNod(RenderWindow& window, const Font& font, const nod* nodCurent)
{
	if (nodCurent == nullptr)
		return;

	Text mainText(nodCurent->date.expresie, font, 16);
	mainText.setFillColor(Color::Black);
	FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(static_cast<int>(marginiText.left + marginiText.width / 2), 10);

	int xPos = nodCurent->date.x;
	int yPos = nodCurent->date.y + 25;
	mainText.setPosition(xPos, yPos);
	window.draw(mainText);

	afisareTextNod(window, font, nodCurent->st);
	afisareTextNod(window, font, nodCurent->dr);
}


void afisareTextLista(RenderWindow& window, const Font& font)
{
	for (const auto A : listaArbori)
	{
		if (A.radacina == nullptr)
			continue;
		afisareTextNod(window, font, A.radacina);
	}
}

string citire(const Event& event)
{
	string s;

	if (event.type == Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			s = static_cast<char>(event.text.unicode);
		}
	}
	return s;
}
