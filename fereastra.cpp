#include <iomanip>
#include <sstream>
#include "testareArbore.h"
#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "evaluareExpresie.h"
#include "executareAlgoritm.h"
#include "functiiExpresie.h"
#include "functiiNod.h"

void functieDebugging(RenderWindow& window, const Font& font)
{
	string textSimboluri = "Nr. de simboluri: " + std::to_string(numarNoduriDinListaArbori());
	Text text1(textSimboluri, font, 16);
	text1.setFillColor(Color::Black);
	text1.setPosition(10, 0);
	window.draw(text1);

	string textArbori = "Nr. de elemente din fiecare arbore:";
	for (int i = 0; i < listaArbori.size(); i++)
		textArbori += " " + to_string(numarNoduriDinArbore(listaArbori[i]));
	Text text2(textArbori, font, 16);
	text2.setFillColor(Color::Black);
	text2.setPosition(10, 15);
	window.draw(text2);

	string textLegaturi = ("Nr. de legaturi: " + to_string(listaLinii.size()));
	Text text3(textLegaturi, font, 16);
	text3.setFillColor(Color::Black);
	text3.setPosition(10, 30);
	window.draw(text3);

	Text text4("Resetaza lista cu 'Del'.", font, 16);
	text4.setFillColor(Color::Black);
	text4.setPosition(840, 0);
	window.draw(text4);

	Text text6("Legatura cu RMB", font, 16);
	text6.setFillColor(Color::Black);
	text6.setPosition(870, 15);
	window.draw(text6);

	//deseneaza pozitia de la mouse pe ecran
	Vector2i pozMouse = Mouse::getPosition(window);
	string textPozMouse = "(" + to_string(pozMouse.x) + "," + to_string(pozMouse.y) + ")";
	Text text5(textPozMouse, font, 16);
	text5.setFillColor(Color::Black);
	text5.setPosition(925, 30);
	window.draw(text5);

	//deseneaza variabilele folosite pe ecran
	string textVariabile = "Variabile:";
	for (const auto& variabila : variabile) {
		textVariabile += "\n" + variabila.first + "= ";

		stringstream stream;
		stream << defaultfloat << setprecision(6) << variabila.second;
		textVariabile += stream.str();
	}

	Text textVariabileAfisate(textVariabile, font, 16);
	textVariabileAfisate.setFillColor(Color::Black);
	textVariabileAfisate.setPosition(10, 55);
	window.draw(textVariabileAfisate);
}

void afisareListaOutput(RenderWindow& window, const Font& font)
{
	if (listaOutput.empty())
		return;
	//deseneaza primul element din listaOutput (ultimul element adaugat) mai intunecat la culoare
	Text textOutput(listaOutput[listaOutput.size() - 1], font, 16);
	textOutput.setFillColor(Color::Black);
	textOutput.setPosition(10, 765);
	window.draw(textOutput);

	//deseneaza restul elementelor din listaOutput mai gri la culoare
	int index = 1;
	for (int i = listaOutput.size() - 2; i >= 0; i--) {
		Text textOutput(listaOutput[i], font, 16);
		textOutput.setFillColor(Color(90, 90, 90));
		textOutput.setPosition(10, 765 - index * 15);
		window.draw(textOutput);
		index++;
	}
}

void logicaInput(const RenderWindow& window, const Event& event)
{
	static nod* nodDeGasit = nullptr;
	static string expresieDeCitit;
	static bool citireExpresie = false;
	static Clock timpCeas;

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{

		if (timpCeas.getElapsedTime().asSeconds() < 1.0f && !citireExpresie)
		{
			nodDeGasit = gasesteNodListaCuPozMouse(window);
			if (nodDeGasit != nullptr)
			{
				citireExpresie = true;
				expresieDeCitit = nodDeGasit->date.expresie;
				cout << "Citire expresie!" << endl;
			}
		}
		else
		{
			if (citireExpresie)
			{
				citireExpresie = false;
				if (!expresieDeCitit.empty() && expresieDeCitit[expresieDeCitit.size() - 1] == '\r') {
					expresieDeCitit = expresieDeCitit.substr(0, expresieDeCitit.size() - 1);//sterge '\r' de la final
				}
				cout << "Expresie citita: " << expresieDeCitit << endl;
				if (nodDeGasit != nullptr)
					nodDeGasit->date.expresie = expresieDeCitit;
				expresieDeCitit.clear();
				logicaAtribuire(nodDeGasit);//temporar. Va trebui mutat.
			}
			timpCeas.restart();
		}
	}
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Enter) {
			citireExpresie = false;
			if (!expresieDeCitit.empty() && expresieDeCitit[expresieDeCitit.size() - 1] == '\r') {
				expresieDeCitit = expresieDeCitit.substr(0, expresieDeCitit.size() - 1);//sterge '\r' de la final
			}
			cout << "Expresie citita: " << expresieDeCitit << endl;
			if (nodDeGasit != nullptr)
				nodDeGasit->date.expresie = expresieDeCitit;
			expresieDeCitit.clear();
			logicaAtribuire(nodDeGasit);//temporar. Va trebui mutat.
		}
		if (event.key.code == Keyboard::F1) {//afiseaza informatia din nodul de afisare
			nod* nodDeAfisat = gasesteNodListaCuPozMouse(window);
			logicaAfisare(nodDeAfisat);
		}
		if (event.key.code == Keyboard::F12) {//executa algoritmul
			executareAlgoritm();
		}
		if (event.key.code == Keyboard::Delete)//resetaza totul
		{
			listaArbori.clear();
			listaLinii.clear();
			listaOutput.clear();
			variabile.clear();
		}
	}
	if (citireExpresie)
	{
		string ch = citire(event);
		if (ch == "\b") {//logica de stergere prin backspace
			if (!expresieDeCitit.empty()) {
				expresieDeCitit = expresieDeCitit.substr(0, expresieDeCitit.size() - 1);
				cout << "Stergere" << endl;
			}
		}
		else if (!ch.empty()) {
			expresieDeCitit += ch;
		}
		if (nodDeGasit != nullptr)//introducerea expresiei citite in nod.
			nodDeGasit->date.expresie = expresieDeCitit;
	}
}

void creareFereastra()
{
	RenderWindow window(VideoMode(1000, 800), "Interschem");
	window.setFramerateLimit(45);//limita de fps ca sa nu bubuie laptopul :')
	window.setKeyRepeatEnabled(false);

	Font font;
	if (!font.loadFromFile("Arial.ttf")) {
		cout << "EROARE: NU S-A INCARCAT FONTUL CORECT!!";
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
			logicaInput(window, event);
		}
		window.clear(Color::White);

		logicaSimboluri(window);//creare, stergere, legare simboluri

		creareSimbolPtListaArbori(window, font);//deseneaza simbolurile din listaArbori
		desenareLinieIntreSimboluri(window);//deseneaza liniile dintre simboluri
		afisareTextLista(window, font);//deseneaza textul fiecarui simbol

		afisareListaOutput(window, font);//deseneaza outputul
		functieDebugging(window, font);//deseneaza informatii de debugging
		window.display();
	}
}
