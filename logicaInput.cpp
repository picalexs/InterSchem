#include "logicaInput.h"
#include "executareAlgoritm.h"
#include "functiiExpresie.h"
#include "logicaSimboluri.h"

void logicaLMB(const RenderWindow& fereastraAplicatie, Clock& timpCeas, bool& citireExpresie, nod*& nodDeGasit, string& expresieDeCitit)
{
	if (timpCeas.getElapsedTime().asSeconds() < 1.0f && !citireExpresie)
	{
		nodDeGasit = gasesteNodListaCuPozMouse(fereastraAplicatie);
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
			cout << "Expresie citita: " << expresieDeCitit << '\n';
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

void logicaExecutareInput(const RenderWindow& fereastraAplicatie,const Event& event)
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
		logicaLMB(fereastraAplicatie,timpCeasLMB, citireExpresie, nodDeGasit, expresieDeCitit);
		timpApasatLMB.restart();
	}
	if (timpApasatLMB.getElapsedTime().asSeconds() >= 0.20f) {
		if (nodDeMutat == nullptr)
			nodDeMutat = gasesteNodListaCuPozMouse(fereastraAplicatie);
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
			nodDeMutat->date.x = Mouse::getPosition(fereastraAplicatie).x;
			nodDeMutat->date.y = Mouse::getPosition(fereastraAplicatie).y;
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
		string ch;
		if (event.type == Event::TextEntered)
		{
			if (event.text.unicode < 128)
			{
				ch = static_cast<char>(event.text.unicode);
			}
		}

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