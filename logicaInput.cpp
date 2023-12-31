#include "logicaInput.h"
#include "executareAlgoritm.h"
#include "functiiExpresie.h"
#include "dimensiuniSimboluri.h"

void logicaLMB(const RenderWindow& fereastraAplicatie, Clock& timpCeas, bool& citireExpresie, Nod*& nodDeGasit, string& expresieDeCitit)
{
	if (timpCeas.getElapsedTime().asSeconds() < 1.0f && !citireExpresie)
	{
		nodDeGasit = gasesteNodListaCuPozMouse(fereastraAplicatie);
		if (nodDeGasit != nullptr)
		{
			if (nodDeGasit->date.tip == 0 || nodDeGasit->date.tip == 1)
			{
				nodDeGasit = nullptr;
				return;
			}

			citireExpresie = true;
			reseteazaModificareDimensiune();
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
void logicaEnter(bool& citireExpresie, Nod* nodDeGasit, string& expresieDeCitit) {
	if (nodDeGasit == nullptr)
		return;
	citireExpresie = false;
	if (!expresieDeCitit.empty() && expresieDeCitit.back() == '\r') {
		expresieDeCitit.pop_back();

		cout << "Expresie citita: " << expresieDeCitit << endl;
		listaConsola.push_back(expresieDeCitit);
		nodDeGasit->date.expresie = expresieDeCitit;
	}

	if (expresieDeCitit.empty() || (expresieDeCitit.size() == 1 && expresieDeCitit.back() == '\r')) {
		nodDeGasit = nullptr;
		expresieDeCitit.clear();
	}
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

void logicaExecutareInput(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	//static initializeaza variabilele doar la prima apelare, ele pastrandu-si valoarea intre apeluri.
	static Nod* nodDeGasit = nullptr;
	static Nod* nodDeMutat = nullptr;
	static bool citireExpresie = false;
	static string expresieDeCitit;
	static Clock timpCeasLMB, timpCeasTastatura, timpApasatLMB;
	static char ultimaTastaApasata;

	if (esteApasatLMB) {//verificare dublu click -> citire expresie
		esteApasatLMB = false;
		esteRidicatLMB = false;
		logicaLMB(fereastraAplicatie, timpCeasLMB, citireExpresie, nodDeGasit, expresieDeCitit);
		timpApasatLMB.restart();
	}
	if (timpApasatLMB.getElapsedTime().asSeconds() >= 0.20f) {
		if (nodDeMutat == nullptr) {
			nodDeMutat = gasesteNodListaCuPozMouse(fereastraAplicatie);
			if (nodDeMutat != nullptr)
			{
				int pozDeMutat = -1;
				Nod* nodGasit = nullptr;
				for (int i = listaArbori.size() - 1; i >= 0; --i) {
					nodGasit = gasesteNodInArbore(listaArbori[i], nodDeMutat->date);
					if (nodGasit != nullptr) {
						pozDeMutat = i;
						break;
					}
				}
				if (pozDeMutat != -1) {
					//punem termenul selectat la final pentru a aparea deasupra celorlalte simboluri
					const Arbore arboreDeMutat = listaArbori[pozDeMutat];
					listaArbori.erase(listaArbori.begin() + pozDeMutat);
					listaArbori.push_back(arboreDeMutat);
				}
			}
		}
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
			nodDeMutat->date.x = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).x;
			nodDeMutat->date.y = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).y;
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
		else
			ultimaTastaApasata = '\0';

		//daca tasta e apasata prelungit, nu se repeta decat daca e tinuta apasat de mai mult de 0.35 secunde
		if (ultimaTastaApasata == ch[0] && timpCeasTastatura.getElapsedTime().asSeconds() < 0.35f)
			return;
		if (ultimaTastaApasata != ch)
			timpCeasTastatura.restart();
		ultimaTastaApasata = ch[0];

		if (ch == "\b") {//logica de stergere prin backspace
			if (!expresieDeCitit.empty()) {
				expresieDeCitit.pop_back();
				modificareLungimeSimbol(desktop, nodDeGasit->date);
				cout << "Stergere\n";
			}
		}
		else if (!ch.empty()) {
			expresieDeCitit += ch;
			modificareLungimeSimbol(desktop, nodDeGasit->date);
		}
		if (nodDeGasit != nullptr)//introducerea expresiei citite in Nod.
			nodDeGasit->date.expresie = expresieDeCitit;
	}
	if (esteApasatEnter)//stop citire expresie
	{
		logicaEnter(citireExpresie, nodDeGasit, expresieDeCitit);
		esteApasatEnter = false;
	}
}