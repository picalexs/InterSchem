#include <SFML/Graphics.hpp>
#include "desenareSimboluri.h"
#include "functiiExpresie.h"
#include "functiiNod.h"
#include "logicaInput.h"
#include "logicaSimboluri.h"
#include "butoaneMeniu.h"
#include "logicaButoane.h"
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
		}
		logicaExecutareInput(fereastraAplicatie, desktop, event);
		fereastraAplicatie.clear(Color::White);

		logicaSimboluri(fereastraAplicatie, desktop);//creare, stergere, legare simboluri

		creareSimbolPtListaArbori(fereastraAplicatie, desktop);//deseneaza simbolurile din listaArbori
		desenareLinieIntreSimboluri(fereastraAplicatie);//deseneaza liniile dintre simboluri
		afisareListaOutput(fereastraAplicatie, desktop);//deseneaza outputul

		butonSalvare(fereastraAplicatie, desktop);
		butonIncarcare(fereastraAplicatie, desktop);
		butonStart(fereastraAplicatie, desktop);
		butonStop(fereastraAplicatie, desktop);
		butonCitire(fereastraAplicatie, desktop);
		butonAfisare(fereastraAplicatie, desktop);
		butonAtribuire(fereastraAplicatie, desktop);
		butonDaca(fereastraAplicatie, desktop);
		butonCatTimp(fereastraAplicatie, desktop);
		butonRulare(fereastraAplicatie, desktop);
		butonConvertire(fereastraAplicatie, desktop);
		butonAjutor(fereastraAplicatie, desktop);

		verificareApasare(fereastraAplicatie, desktop, event);
		///functieDebugging(fereastraAplicatie, desktop);//deseneaza informatii de debugging
		fereastraAplicatie.display();
	}
}
