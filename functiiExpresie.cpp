#include "functiiExpresie.h"

void afisareTextNod(RenderWindow& window, const Font& font, const nod* nodCurent)
{
	if (nodCurent == nullptr)
		return;

	int marimeFont = 16;
	Text text1("T", font, marimeFont);
	FloatRect marginiT = text1.getLocalBounds();
	int inaltimeT = static_cast<int>(marginiT.height);

	Text mainText(nodCurent->date.expresie, font, marimeFont);
	FloatRect marginiText = text1.getLocalBounds();
	mainText.setFillColor(Color::Black);
	mainText.setOrigin((int)(marginiText.left + marginiText.width / 2), (int)(marginiText.top + inaltimeT / 2));

	int xPos = round(nodCurent->date.x);
	int yPos = round(nodCurent->date.y + 25);

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
