#include "logicaInput.h"
#include "desenareLinie.h"
#include "executareAlgoritm.h"
#include "functiiExpresie.h"
#include "dimensiuniSimboluri.h"
#include "evaluareExpresie.h"
#include "logicaExecutare.h"

void logicaLMB(const RenderWindow& fereastraAplicatie, Clock& timpCeas, bool& citireExpresie, Nod*& nodDeGasit, string& expresieDeCitit)
{
	if (timpCeas.getElapsedTime().asSeconds() < 1.0f && !citireExpresie)
	{
		nodDeGasit = gasesteNodListaCuPozMouse(fereastraAplicatie);
		if (nodDeGasit != nullptr)
		{
			if (nodDeGasit->date.tip == TipNod::START || nodDeGasit->date.tip == TipNod::STOP)
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

void citireExpresie(const Event& event, string& expresieDeCitit)
{
	string ch;
	static char ultimaTastaApasata;
	static Clock timpCeasTastatura;
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
			cout << "Stergere\n";
		}
	}
	else if (!ch.empty()) {
		expresieDeCitit += ch;
	}
}

void logicaExecutareInput(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	//static initializeaza variabilele doar la prima apelare, ele pastrandu-si valoarea intre apeluri.
	static Nod* nodDeGasit = nullptr;
	static Nod* nodDeMutat = nullptr;
	static Nod* nodDeMutatTata = nullptr;
	static int pozDeMutat = -1;
	static bool seCitesteExpresie = false;
	static string expresieDeCitit;
	static Clock timpCeasLMB, timpApasatLMB;
	static bool seCitesteParcurgere = false;

	if (esteApasatLMB) {//verificare dublu click -> citire expresie
		esteApasatLMB = false;
		esteRidicatLMB = false;
		logicaLMB(fereastraAplicatie, timpCeasLMB, seCitesteExpresie, nodDeGasit, expresieDeCitit);
		timpApasatLMB.restart();
	}
	if (timpApasatLMB.getElapsedTime().asSeconds() >= 0.20f) {
		if (nodDeMutat == nullptr) {
			nodDeMutat = gasesteNodListaCuPozMouse(fereastraAplicatie);
			if (nodDeMutat != nullptr)
			{
				pozDeMutat = -1;
				const Nod* nodGasit = nullptr;
				for (int i = listaArbori.size() - 1; i >= 0; --i) {
					nodGasit = gasesteNodInArbore(listaArbori[i], nodDeMutat->date);
					if (nodGasit != nullptr) {
						pozDeMutat = i;
						break;
					}
				}
				if (pozDeMutat != -1) {
					//punem termenul selectat la final pentru a aparea deasupra celorlalte simboluri
					nodDeMutatTata = gasesteNodTata(listaArbori[pozDeMutat].radacina, nodDeMutat);
					const Arbore arboreDeMutat = listaArbori[pozDeMutat];
					listaArbori.erase(listaArbori.begin() + pozDeMutat);
					listaArbori.push_back(arboreDeMutat);
				}
			}
		}
	}
	static unordered_set<short> iduriLiniiDeActualizat;
	static unordered_set<Nod*> noduriDeActualizat;
	if (esteRidicatLMB)
	{
		for (const auto& nod : noduriDeActualizat) {
			adaugaSimbolCaObstacole(nod);
		}
		for (const auto& linie : iduriLiniiDeActualizat) {
			actualizeazaLinieObstacolPrinId(linie, nodDeMutat);
		}
		iduriLiniiDeActualizat.clear();
		noduriDeActualizat.clear();
		nodDeMutat = nullptr;
		pozDeMutat = -1;
		timpApasatLMB.restart();
	}
	else
	{
		if (nodDeMutat != nullptr)
		{
			const Nod* nodSt = nodDeMutat->st;
			const Nod* nodDr = nodDeMutat->dr;
			stergereLiniiObstacoleCuNodulDat(nodDeMutat);
			stergeSimbolObstacol(nodDeMutat);
			nodDeMutat->date.x = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).x;
			nodDeMutat->date.y = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).y;

			const set<short> valoareSuprapusa = verificareSuprapunere(nodDeMutat);
			for (auto& valoare : valoareSuprapusa)
			{
				if (valoare > 0) {
					if (iduriLiniiDeActualizat.count(valoare) == 0) {
						iduriLiniiDeActualizat.insert(valoare);
					}
				}
				else if (valoare < 0)
				{
					Nod* nodDeInserat = gasesteNodObstacolInLista(nodDeMutat);
					if (nodDeInserat == nullptr)
						return;
					if (noduriDeActualizat.count(nodDeInserat) == 0)
						noduriDeActualizat.insert(nodDeInserat);
				}
			}

			for (const auto& nod : noduriDeActualizat) {
				adaugaSimbolCaObstacole(nod);
			}
			for (const auto& idLinie : iduriLiniiDeActualizat) {
				actualizeazaLinieObstacolPrinId(idLinie, nodDeMutat);
			}
			adaugaSimbolCaObstacole(nodDeMutat);
			if (nodDeMutatTata != nullptr)
				adaugaLinieObstacol(nodDeMutatTata, nodDeMutat);
			if (nodSt != nullptr)
				adaugaLinieObstacol(nodDeMutat, nodSt);
			if (nodDr != nullptr)
				adaugaLinieObstacol(nodDeMutat, nodDr);
		}
	}
	if (esteApasatF12)//executa algoritmul
	{
		if (!seCitesteParcurgere)
			logicaF12();
		esteApasatF12 = false;
	}
	if (esteApasatDelete)//resetaza totul
	{
		logicaDelete();
		esteApasatDelete = false;
	}
	if (seCitesteExpresie)
	{
		citireExpresie(event, expresieDeCitit);
		modificareLungimeSimbol(desktop, nodDeGasit->date);
		if (nodDeGasit != nullptr)
			nodDeGasit->date.expresie = expresieDeCitit;
	}
	if (seCitestePtParcurgere())
	{
		citireExpresie(event, expresieDeCitit);
		seCitesteParcurgere = true;
	}

	if (esteApasatEnter)//stop citire expresie
	{
		esteApasatEnter = false;
		if (seCitesteParcurgere)
		{
			if (!expresieDeCitit.empty() && expresieDeCitit.back() == '\r')
				expresieDeCitit.pop_back();
			const long double rezultat = evaluareExpresie(expresieDeCitit);
			seteazaVariabila(getNumeVariabila(), rezultat);
			const string output = "S-a atribuit variabilei " + getNumeVariabila() + " valoarea " + to_string(rezultat);
			cout << output << '\n';
			stopCitirePtParcurgere();
			seCitesteParcurgere = false;
			esteApasatF12 = true;
		}
		else {
			logicaEnter(seCitesteExpresie, nodDeGasit, expresieDeCitit);
		}
		expresieDeCitit.clear();
	}
}