#include <SFML/Graphics.hpp>
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "functiiExpresie.h"
#include "functiiNod.h"
#include "logicaInput.h"
#include "logicaSimboluri.h"
using namespace sf;

void creareFereastra()
{
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(desktop, "Interschem", Style::Default);
	View view(FloatRect(0, 0, desktop.width, desktop.height));
	window.setView(view);

	window.setFramerateLimit(60);//limita de fps ca sa nu bubuie laptopul :')
	window.setKeyRepeatEnabled(false);

	if (fontGlobal.getInfo().family != "Arial")
		if (!fontGlobal.loadFromFile("Arial.ttf")) {
			cout<<"Eroare la incarcarea fontului.\n";
			return;
		}

	atribuireConstanteCunoscute();//PI, e, g, phi;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			logicaInput(event);
		}
		logicaExecutareInput(window, event);
		window.clear(Color::White);

		logicaSimboluri(window);//creare, stergere, legare simboluri

		creareSimbolPtListaArbori(window);//deseneaza simbolurile din listaArbori
		desenareLinieIntreSimboluri(window);//deseneaza liniile dintre simboluri
		afisareTextLista(window,desktop);//deseneaza textul fiecarui simbol
		afisareListaOutput(window, desktop);//deseneaza outputul

		functieDebugging(window,desktop);//deseneaza informatii de debugging
		window.display();
	}
}
