#include "testareArbore.h"
#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "functiiExpresie.h"
#include "functiiNod.h"

void functieDebugging(RenderWindow& window)
{
	Font font;
	font.loadFromFile("Arial.ttf");
	string textSimboluri = "Nr. de simboluri: " + std::to_string(numarNoduriDinListaArbori());
	Text text1(textSimboluri, font, 16);
	text1.setFillColor(Color::Black);
	text1.setPosition(0, 0);
	window.draw(text1);

	string textArbori = "Nr. de elemente din fiecare arbore:";
	for (int i = 0; i < listaArbori.size(); i++)
		textArbori += " " + to_string(numarNoduriDinArbore(listaArbori[i]));
	Text text2(textArbori, font, 16);
	text2.setFillColor(Color::Black);
	text2.setPosition(0, 15);
	window.draw(text2);

	string textLegaturi = ("Nr. de legaturi: " + to_string(listaLinii.size()));
	Text text3(textLegaturi, font, 16);
	text3.setFillColor(Color::Black);
	text3.setPosition(0, 30);
	window.draw(text3);

	Text text4("Resetaza lista cu 'Del'.", font, 16);
	text4.setFillColor(Color::Black);
	text4.setPosition(840, 0);
	window.draw(text4);

	Text text6("Legatura cu RMB", font, 16);
	text6.setFillColor(Color::Black);
	text6.setPosition(870, 15);
	window.draw(text6);

	Vector2i pozMouse = Mouse::getPosition(window);
	string textPozMouse = "(" + to_string(pozMouse.x) + "," + to_string(pozMouse.y) + ")";
	Text text5(textPozMouse, font, 16);
	text5.setFillColor(Color::Black);
	text5.setPosition(925, 30);
	window.draw(text5);
}

void creareFereastra()
{
	RenderWindow window(VideoMode(1000, 800), "Interschem");
	window.setFramerateLimit(45);
	nod* nodDeGasit = nullptr;
	string expresieDeCitit;
	bool citireExpresie = false;
	Clock timpCeas;
	Font font;
	if (!font.loadFromFile("Arial.ttf")) {
		cout << "EROARE NU S-A INCARCAT FONTUL CORECT!!";
		return;
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (timpCeas.getElapsedTime().asSeconds() < 1.0f)
				{
					nodDeGasit = gasesteNodListaCuPozMouse(window);
					if (nodDeGasit != nullptr)
					{
						citireExpresie = true;
						cout << "Citire expresie!" << endl;
					}
				}
				else
				{
					timpCeas.restart();
				}
			}
			if (citireExpresie == true)
			{
				expresieDeCitit += citire(event);
				if (nodDeGasit != nullptr)
					nodDeGasit->date.expresie = expresieDeCitit;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Delete))
		{
			listaArbori.clear();
			listaLinii.clear();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter) && citireExpresie)
		{
			citireExpresie = false;
			cout << "Expresie citita: " << expresieDeCitit << endl;
			expresieDeCitit.clear();
		}

		window.clear(Color::White);

		logicaCreareSimbol(window);
		logicaStergereSimbol(window);
		//logicaLegaturaIntreSimboluri(window);

		creareSimbolPtListaArbori(window, font);

		mutareForma(window);

		desenareLinieIntreSimboluri(window);
		afisareTextLista(window, font);
		functieDebugging(window);
		window.display();
	}
}
