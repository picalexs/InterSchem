#include <SFML/Graphics.hpp>
#include "desenareLinie.h"
#include "desenareSimboluri.h"
#include "functiiExpresie.h"
#include "functiiNod.h"
#include "incarcareDate.h"
#include "logicaInput.h"
#include "logicaSimboluri.h"
#include "salvareDate.h"
#include "butoaneMeniu.h"
#include "logicaButoane.h"
#include "convertireCPlusPlus.h"
using namespace sf;

void creareFereastra()
{
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow fereastraAplicatie(desktop, "Interschem", Style::Default); //de schimbat cu Fullscreen dupa
	const View view(FloatRect(0, 0, static_cast<float>(desktop.width), static_cast<float>(desktop.height)));
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
			static bool apasatF10 = false;
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::F10 && !apasatF10) {
					apasatF10 = true;
					salvareDate();
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::F10) {
				apasatF10 = false;
			}

			static bool apasatF9 = false;
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::F9 && !apasatF9) {
					apasatF9 = true;
					incarcareDate();
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::F9) {
				apasatF9 = false;
			}
			////////////////////////////////////////////////////////////
		}
		logicaExecutareInput(fereastraAplicatie, desktop, event);
		fereastraAplicatie.clear(Color::White);

		creareSimbolPtListaArbori(fereastraAplicatie, desktop);//deseneaza simbolurile din listaArbori
		desenareLinii(fereastraAplicatie);//deseneaza liniile dintre simboluri
		afisareListaOutput(fereastraAplicatie, desktop);//deseneaza outputul

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4)
			convertire(fereastraAplicatie, desktop);

		butonSalvare(fereastraAplicatie, desktop);
		butonIncarcare(fereastraAplicatie, desktop);

		butonDropDown(fereastraAplicatie, desktop);
		butonRulare(fereastraAplicatie, desktop);
		butonConvertire(fereastraAplicatie, desktop);
		butonAjutor(fereastraAplicatie, desktop);

		logicaButon(fereastraAplicatie, desktop, event);
		///functieDebugging(fereastraAplicatie, desktop);//deseneaza informatii de debugging
		fereastraAplicatie.display();
	}
}
