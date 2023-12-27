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
	if (listaConsola.empty())
		return;
	//deseneaza primul element din listaConsola (ultimul element adaugat) mai intunecat la culoare
	Text textOutput(listaConsola[listaConsola.size() - 1], font, 16);
	textOutput.setFillColor(Color::Black);
	textOutput.setPosition(10, 765);
	window.draw(textOutput);

	//deseneaza restul elementelor din listaConsola mai gri la culoare
	int index = 1;
	for (int i = listaConsola.size() - 2; i >= 0; i--) {
		Text textOutput(listaConsola[i], font, 16);
		textOutput.setFillColor(Color(90, 90, 90));
		textOutput.setPosition(10, 765 - index * 15);
		window.draw(textOutput);
		index++;
	}
}

void logicaLMB(const RenderWindow& window, Clock& timpCeas, bool& citireExpresie, nod*& nodDeGasit, string& expresieDeCitit)
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
		}
		timpCeas.restart();
	}
}

void logicaEnter(bool& citireExpresie, nod* nodDeGasit, string& expresieDeCitit)
{
	citireExpresie = false;
	if (!expresieDeCitit.empty() && expresieDeCitit[expresieDeCitit.size() - 1] == '\r') {
		expresieDeCitit = expresieDeCitit.substr(0, expresieDeCitit.size() - 1);//sterge '\r' de la final
	}
	cout << "Expresie citita: " << expresieDeCitit << endl;
	if (esteActivaCitireaPtAlgoritm()) {
		listaConsola.push_back(expresieDeCitit);
		opresteCitireaPtAlgoritm();
	}
	else if (nodDeGasit != nullptr)
		nodDeGasit->date.expresie = expresieDeCitit;
	expresieDeCitit.clear();
}

void logicaF12()
{
	executareAlgoritm();
}

void logicaDelete()
{
	listaArbori.clear();
	listaLinii.clear();
	listaConsola.clear();
	variabile.clear();
	atribuireConstanteCunoscute();//PI, e, g, phi;
}

bool esteApasatLMB = false;
bool esteRidicatLMB = true;
bool esteApasatEnter = false;
bool esteApasatF12 = false;
bool esteApasatDelete = false;

void logicaInput(const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		esteApasatLMB = true;
	}
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		esteRidicatLMB = true;
	}
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Enter) {
			esteApasatEnter = true;
		}
		if (event.key.code == Keyboard::F12) {
			esteApasatF12 = true;
		}
		if (event.key.code == Keyboard::Delete)
		{
			esteApasatDelete = true;
		}
	}
}

void logicaExecutareInput(const RenderWindow& window, const Event& event)
{
	//static initializeaza variabilele doar la prima apelare, ele pastrandu-si valoarea intre apeluri.
	static nod* nodDeGasit = nullptr;
	static nod* nodDeMutat = nullptr;
	static bool citireExpresie = false;
	static string expresieDeCitit;
	static Clock timpCeasLMB, timpCeasTastatura, timpApasatLMB;
	static char ultimaTastaApasata;

	if (esteApasatLMB) {//verificare dublu click -> citire expresie
		esteApasatLMB = false;
		esteRidicatLMB = false;
		logicaLMB(window, timpCeasLMB, citireExpresie, nodDeGasit, expresieDeCitit);
		timpApasatLMB.restart();
	}
	if (timpApasatLMB.getElapsedTime().asSeconds() >= 0.30f) {
		if (nodDeMutat == nullptr)
			nodDeMutat = gasesteNodListaCuPozMouse(window);
	}
	if (esteRidicatLMB)
	{
		nodDeMutat = nullptr;
		timpApasatLMB.restart();
	}
	else
	{
		if (nodDeMutat != nullptr)
		{
			nodDeMutat->date.x = Mouse::getPosition(window).x;
			nodDeMutat->date.y = Mouse::getPosition(window).y;
		}
	}
	if (esteApasatF12)//executa algoritmul
	{
		logicaF12();
		esteApasatF12 = false;
	}
	if (esteApasatDelete)//resetaza totul
	{
		logicaDelete();
		esteApasatDelete = false;
	}
	if (citireExpresie)
	{
		string ch = citire(event);
		//daca tasta e apasata in continuu, nu se repeta decat daca e tinuta apasat de mai mult de 0.35 secunde
		if (ultimaTastaApasata == ch[0] && timpCeasTastatura.getElapsedTime().asSeconds() < 0.35f)
			return;
		if (ultimaTastaApasata != ch)
			timpCeasTastatura.restart();
		ultimaTastaApasata = ch[0];

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
	if (esteApasatEnter)//stop citire expresie
	{
		logicaEnter(citireExpresie, nodDeGasit, expresieDeCitit);
		esteApasatEnter = false;
	}
}

void creareFereastra()
{
	RenderWindow window(VideoMode(1000, 800), "Interschem");
	window.setFramerateLimit(60);//limita de fps ca sa nu bubuie laptopul :')
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
			logicaInput(event);
		}
		logicaExecutareInput(window, event);
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
