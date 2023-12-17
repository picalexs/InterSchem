#include "functiiExpresie.h"

void afisareTextNod(RenderWindow& window, const Font& font, const nod* nodCurent)
{
	if (nodCurent == nullptr)
		return;

	Text text1(nodCurent->date.expresie, font, 16);
	text1.setFillColor(Color::Black);
	text1.setPosition(nodCurent->date.x, nodCurent->date.y);
	window.draw(text1);
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
		if (event.text.unicode < 128 && event.text.unicode != 8)
		{
			s = static_cast<char>(event.text.unicode);
			///std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
		}
	}
	return s;
}
