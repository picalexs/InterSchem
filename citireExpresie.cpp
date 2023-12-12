#include "citireExpresie.h"
#include "fereastra.h"

void afisareTextNod(RenderWindow& window, nod* nodCurent) {
	if (nodCurent == nullptr)
		return;
	///afisez pe ecran cu text font nodCurent->date.x  nodCurent->date.y
	Font font;
	font.loadFromFile("Arial.ttf");
	Text text1(nodCurent->date.expresie, font, 16);
	text1.setFillColor(Color::Black);
	text1.setPosition(nodCurent->date.x, nodCurent->date.y);
	window.draw(text1);
	afisareTextNod(window, nodCurent->st);
	afisareTextNod(window, nodCurent->dr);
}


void afisareTextLista(RenderWindow& window)
{
	for (auto A : listaArbori)
	{
		if (A.radacina == nullptr)
			return;
		return afisareTextNod(window, A.radacina);
	}
}



string citire(const sf::Event& event)
{
    string s;

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode != 8) {
            s = static_cast<char>(event.text.unicode);
            ///std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
        }
    }
    return s;
}