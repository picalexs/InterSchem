#include <SFML/Graphics.hpp>
#include <windows.h>
#include "desenareLinie.h"
#include "desenareSimboluri.h"
#include "functiiExpresie.h"
#include "functiiNod.h"
#include "incarcareDate.h"
#include "logicaInput.h"
#include "salvareDate.h"
#include "convertireCPlusPlus.h"
#include "desenareButoaneMeniu.h"
#include "logicaButoane.h"
using namespace sf;

void creareFereastra()
{
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow fereastraAplicatie(desktop, "Interschem", Style::Default); //de schimbat cu Fullscreen dupa
	const View view(FloatRect(0, 0, static_cast<float>(desktop.width), static_cast<float>(desktop.height)));
	::ShowWindow(fereastraAplicatie.getSystemHandle(), SW_MAXIMIZE);
	fereastraAplicatie.setView(view);
	fereastraAplicatie.setFramerateLimit(60);//limita de fps ca sa nu bubuie laptopul :')
	fereastraAplicatie.setKeyRepeatEnabled(false);

	if (fontGlobal.getInfo().family != "Arial")
		if (!fontGlobal.loadFromFile("Arial.ttf")) {
			cout << "Eroare la incarcarea fontului.\n";
			return;
		}

	atribuireConstanteCunoscute();//PI, e, g, phi;
	initializareMatriceObstacole(desktop);
	setDimensiuniStandard(desktop);

	while (fereastraAplicatie.isOpen())
	{
		Event event;
		while (fereastraAplicatie.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				fereastraAplicatie.close();
			}
			logicaInput(event);
			//////////////////////////DEBUGGING//////////////////////////
			static bool apasatF11 = false;
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::F11 && !apasatF11) {
					apasatF11 = true;
					afisareMatrice();
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::F11) {
				apasatF11 = false;
			}

			static bool apasatF10 = false;
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::F10 && !apasatF10) {
					apasatF10 = true;
					salvareDate(desktop);
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::F10) {
				apasatF10 = false;
			}

			static bool apasatF9 = false;
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::F9 && !apasatF9) {
					apasatF9 = true;
					incarcareDate(desktop);
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::F9) {
				apasatF9 = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4)
				convertire(fereastraAplicatie, desktop);
			////////////////////////////////////////////////////////////
		}
		fereastraAplicatie.clear(Color::White);
		logicaExecutareInput(fereastraAplicatie, desktop, event);
		logicaButon(fereastraAplicatie, desktop, event);
		butoaneMeniu(fereastraAplicatie, desktop);

		creareSimbolPtListaArbori(fereastraAplicatie, desktop);//deseneaza simbolurile din listaArbori
		desenareLinii(fereastraAplicatie, desktop);//deseneaza liniile dintre simboluri
		afisareListaOutput(fereastraAplicatie, desktop);//afiseaza listaConsola
		afisareVariabile(fereastraAplicatie, desktop);//afiseaza variabilele pe ecran

		//functieDebugging(fereastraAplicatie, desktop);//deseneaza informatii de debugging
		fereastraAplicatie.display();
	}
}
