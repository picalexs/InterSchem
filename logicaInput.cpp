#include "logicaInput.h"
#include "desenareLinie.h"
#include "executareAlgoritm.h"
#include "functiiExpresie.h"
#include "dimensiuniSimboluri.h"
#include "evaluareExpresie.h"
#include "logicaExecutare.h"
#include "logicaSimboluri.h"
#include "salvareDate.h"

string expresieDeCitit;

void logicaEnterParcurgere(bool& seCitesteParcurgere, bool& esteApasatF12)
{
	if (!expresieDeCitit.empty() && expresieDeCitit.back() == '\r')
		expresieDeCitit.pop_back();

	const long double rezultat = evaluareExpresie(expresieDeCitit);
	stringstream stream;
	stream << defaultfloat << setprecision(6) << rezultat;
	listaConsola.push_back(stream.str());

	seteazaVariabila(getNumeVariabila(), rezultat);
	const string output = "S-a atribuit variabilei " + getNumeVariabila() + " valoarea " + to_string(rezultat);
	cout << output << '\n';
	stopCitirePtParcurgere();
	seCitesteParcurgere = false;
	esteApasatF12 = true;
}

void logicaEnterSalvare(bool& seCitestePtSalvare)
{
	seCitestePtSalvare = false;
}

void logicaEnter(bool& citireExpresie, Nod* nodDeGasit) {
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

bool esteDubluClick(const Clock& timpCeas, const bool& citireExpresie)
{
	return timpCeas.getElapsedTime().asSeconds() < 1.0f && citireExpresie == false;
}

void logicaDubluClick(const RenderWindow& fereastraAplicatie, bool& citireExpresie, Nod*& nodDeGasit)
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

void logicaLMB(const RenderWindow& fereastraAplicatie, bool& seCitesteExpresie, bool& esteApasatLMB, bool& esteRidicatLMB, Nod*& nodDeGasit, Clock& timpCeasLMB, Clock& timpApasatLMB)
{
	if (esteDubluClick(timpCeasLMB, seCitesteExpresie)) {
		logicaDubluClick(fereastraAplicatie, seCitesteExpresie, nodDeGasit);
	}
	else
	{
		if (seCitesteExpresie)
		{
			if (!expresieDeCitit.empty() && expresieDeCitit[expresieDeCitit.size() - 1] == '\r') {
				expresieDeCitit = expresieDeCitit.substr(0, expresieDeCitit.size() - 1);//sterge '\r' de la final
			}
			cout << "Expresie citita: " << expresieDeCitit << '\n';
			if (nodDeGasit != nullptr)
				nodDeGasit->date.expresie = expresieDeCitit;
			seCitesteExpresie = false;
			expresieDeCitit.clear();
		}
		timpCeasLMB.restart();
	}
	esteApasatLMB = false;
	esteRidicatLMB = false;
	timpApasatLMB.restart();
}

void actualizareSimbolDeMutat(const RenderWindow& fereastraAplicatie, Nod*& nodDeMutat, Nod*& nodLegatDeWhile,
	const Clock& timpApasatLMB, vector<pair<Nod*, unsigned>>& noduriDeLegatSpreNod, vector<pair<Nod*, unsigned>>& noduriDeLegatDinNod)
{
	if (timpApasatLMB.getElapsedTime().asSeconds() < 0.20f)
		return;
	if (nodDeMutat != nullptr)
		return;
	nodDeMutat = gasesteNodListaCuPozMouse(fereastraAplicatie);
	if (nodDeMutat == nullptr)
		return;

	noduriDeLegatSpreNod = toateLiniileCuNodStop(nodDeMutat);
	noduriDeLegatDinNod = toateLiniileCuNodStart(nodDeMutat);

	int pozDeMutat = -1;
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
		if (nodDeMutat->date.tip == TipNod::CAT_TIMP)
		{
			nodLegatDeWhile = gasesteNodLegatDeWhile(nodDeMutat);
		}
		const Arbore arboreDeMutat = listaArbori[pozDeMutat];
		listaArbori.erase(listaArbori.begin() + pozDeMutat);
		listaArbori.push_back(arboreDeMutat);
	}
}

void logicaMutareSimbol(const RenderWindow& fereastraAplicatie, Nod*& nodDeMutat, Nod*& nodLegatDeWhile,
	set<unsigned>& iduriLiniiDeActualizat, set<Nod*>& noduriDeActualizat, const vector<pair<Nod*, unsigned>>& noduriDeLegatSpreNod, const vector<pair<Nod*, unsigned>>& noduriDeLegatDinNod)
{
	if (nodDeMutat == nullptr)
		return;

	stergereLiniiObstacoleCuNodulDat(nodDeMutat);
	stergeSimbolObstacol(nodDeMutat);

	nodDeMutat->date.x = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).x;
	nodDeMutat->date.y = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).y;

	set<int> valoareSuprapusa;
	verificareSuprapunere(valoareSuprapusa, nodDeMutat);
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

	adaugaSimbolCaObstacole(nodDeMutat);
	for (const auto& nod : noduriDeActualizat) {
		adaugaSimbolCaObstacole(nod);
	}

	for (const auto& idLinie : iduriLiniiDeActualizat) {
		actualizeazaLinieObstacolPrinId(idLinie, nodDeMutat, { 0 });
	}
	for (const auto& it : noduriDeLegatDinNod)
	{
		bool linieSpreWhile = false;
		if (it.first->date.tip == TipNod::CAT_TIMP)
		{
			if (gasesteNodLegatDeWhile(it.first) != nullptr && gasesteNodLegatDeWhile((nodDeMutat)) != nullptr)
				linieSpreWhile = true;
		}
		adaugaLinieObstacol(nodDeMutat, it.first, linieSpreWhile, it.second, { 0 });
	}
	vector<unsigned> poateTrecePrinIduri;
	poateTrecePrinIduri.reserve(noduriDeLegatSpreNod.size());
	for (const auto& it : noduriDeLegatSpreNod)
	{
		poateTrecePrinIduri.push_back(it.second);
	}
	for (const auto& it : noduriDeLegatSpreNod) {
		adaugaLinieObstacol(it.first, nodDeMutat, false, it.second, poateTrecePrinIduri);
	}
	if (nodLegatDeWhile != nullptr) {
		adaugaLinieObstacol(nodLegatDeWhile, nodDeMutat, true, 0, { 0 });
	}
}

void stopMutareSimbol(set<unsigned>& iduriLiniiDeActualizat, set<Nod*> noduriDeActualizat, vector<pair<Nod*, unsigned>>& noduriDeLegatSpreNod,
	vector<pair<Nod*, unsigned>>& noduriDeLegatDinNod, Nod*& nodDeMutat, Nod*& nodLegatDeWhile, Clock& timpApasatLMB)
{
	for (const auto& nod : noduriDeActualizat) {
		adaugaSimbolCaObstacole(nod);
	}
	for (const auto& linie : iduriLiniiDeActualizat) {
		actualizeazaLinieObstacolPrinId(linie, nodDeMutat, { 0 });
	}

	iduriLiniiDeActualizat.clear();
	noduriDeActualizat.clear();
	noduriDeLegatSpreNod.clear();
	noduriDeLegatDinNod.clear();
	nodLegatDeWhile = nullptr;
	nodDeMutat = nullptr;
	timpApasatLMB.restart();
}

void logicaDelete()
{
	liniiDeDesenat.clear();
	listaArbori.clear();
	listaConsola.clear();
	variabile.clear();
	resetMatrice();
	liniiDeDesenat.clear();
	atribuireConstanteCunoscute();//PI, e, g, phi;
}

bool esteApasatLMB = false;
bool esteRidicatLMB = true;
bool esteApasatEnter = false;
bool esteApasatF1 = false;
bool esteApasatF2 = false;
bool esteApasatDelete = false;

int esteApasatCreare = 0;
bool esteApasatStergere = false;
bool esteApasatLegare = false;
bool esteRidicatLegare = false;

bool seCitesteExpresie = false;
bool seCitesteParcurgere = false;
bool seCitestePtSalvare = false;

bool seCitesteSalvare()
{
	return seCitestePtSalvare;
}

void activeazaSalvare()
{
	seCitestePtSalvare = true;
}

void opresteSalvare()
{
	seCitestePtSalvare = false;
}

string getNumeFisierSalvare()
{
	return expresieDeCitit;
}

bool seCitesteParcurgereProgram()
{
	return seCitesteParcurgere;
}

void activeazaParcurgereaTotala()
{
	esteApasatF2 = true;
}

void logicaInput(const Event& event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left) {
			esteApasatLMB = true;
		}
		if (event.mouseButton.button == Mouse::Right) {
			esteApasatLegare = true;
		}
	}
	if (event.type == Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == Mouse::Left) {
			esteRidicatLMB = true;
		}
		if (event.mouseButton.button == Mouse::Right)
		{
			esteRidicatLegare = true;
		}
	}

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Enter) {
			esteApasatEnter = true;
		}
		if (event.key.code == Keyboard::F1) {
			esteApasatF1 = true;
		}
		if (event.key.code == Keyboard::F2) {
			esteApasatF2 = true;
			if (!esteAlgoritmCorect())
				esteApasatF2 = false;
		}
		if (event.key.code == Keyboard::Delete)
		{
			esteApasatDelete = true;
		}
		if (!seCitesteExpresie && !seCitesteParcurgere && !seCitestePtSalvare) {//input creare simbol
			for (int i = Keyboard::Num0; i <= Keyboard::Num6; ++i) {
				if (event.key.code == i) {
					esteApasatCreare = i - Keyboard::Num0;
					break;
				}
			}
		}
		if (!seCitesteExpresie && !seCitesteParcurgere && !seCitestePtSalvare &&
			(event.key.code == Keyboard::BackSpace || event.key.code == Keyboard::Escape))//input stergere simbol
		{
			esteApasatStergere = true;
		}
	}
}

void citireExpresie(const Event& event)
{
	string ch;
	static char ultimaTastaApasata;
	static Clock timpCeasTastatura;
	if (event.type == Event::TextEntered)
	{
		const auto caracter = event.text.unicode;
		if (caracter < 128 && (isprint(caracter) || caracter == '\b')) // Verifica daca este un caracter ce se poate afisa ca char
		{
			ch = static_cast<char>(caracter);
		}
		else {
			return; // Ignore non-printable characters
		}
	}
	else {
		ultimaTastaApasata = '\0';
	}

	// Repeta simbolul doar daca tasta este apasata mai mult de 0.35 secunde
	if (ultimaTastaApasata == ch[0] && timpCeasTastatura.getElapsedTime().asSeconds() < 0.35f)
		return;
	if (ultimaTastaApasata != ch)
		timpCeasTastatura.restart();
	ultimaTastaApasata = ch[0];

	if (ch == '\b') { // Stergere caractere
		if (!expresieDeCitit.empty()) {
			expresieDeCitit.pop_back();
		}
	}
	else if (!ch.empty()) {
		expresieDeCitit += ch;
	}
}

void logicaExecutareInput(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	static Nod* nodDeGasit = nullptr;
	static Nod* nodDeMutat = nullptr;
	static Nod* nodLegatDeWhile = nullptr;
	static Clock timpCeasLMB, timpApasatLMB;
	static set<unsigned> iduriLiniiDeActualizat;
	static set<Nod*> noduriDeActualizat;
	static vector<pair<Nod*, unsigned>> noduriDeLegatSpreNod;
	static vector<pair<Nod*, unsigned>> noduriDeLegatDinNod;

	if (esteApasatLMB) {
		logicaLMB(fereastraAplicatie, seCitesteExpresie, esteApasatLMB, esteRidicatLMB, nodDeGasit, timpCeasLMB, timpApasatLMB);
	}
	actualizareSimbolDeMutat(fereastraAplicatie, nodDeMutat, nodLegatDeWhile, timpApasatLMB, noduriDeLegatSpreNod, noduriDeLegatDinNod);
	if (esteRidicatLMB)
	{
		stopMutareSimbol(iduriLiniiDeActualizat, noduriDeActualizat, noduriDeLegatSpreNod, noduriDeLegatDinNod, nodDeMutat, nodLegatDeWhile, timpApasatLMB);
	}
	else
	{
		logicaMutareSimbol(fereastraAplicatie, nodDeMutat, nodLegatDeWhile, iduriLiniiDeActualizat, noduriDeActualizat, noduriDeLegatSpreNod, noduriDeLegatDinNod);
	}
	if (esteApasatCreare != 0)
	{
		logicaCreareSimbol(fereastraAplicatie, desktop, esteApasatCreare - 1);
		esteApasatCreare = 0;
	}
	if (esteApasatStergere)
	{
		logicaStergereSimbol(fereastraAplicatie);
		esteApasatStergere = false;
	}
	if (esteApasatLegare)
	{
		logicaGasireNoduriDeLegat(fereastraAplicatie);
	}
	if (esteRidicatLegare)
	{
		logicaLegaturaIntreSimboluri(false, { 0 });
		esteApasatLegare = false;
		esteRidicatLegare = false;
	}
	if (esteApasatF1)//pas de executare 
	{
		if (!seCitesteParcurgere)
			executareAlgoritmPasCuPas();
		esteApasatF1 = false;
	}
	if (esteApasatF2)//executa algoritmul
	{
		if (!seCitesteParcurgere)
			executareTotAlgoritm();

		static bool saInceputParcurgerea = false;
		if (seParcurgeAlgoritmul())
			saInceputParcurgerea = true;
		if (!seParcurgeAlgoritmul() && saInceputParcurgerea) {
			esteApasatF2 = false;
			saInceputParcurgerea = false;
		}
	}
	if (esteApasatDelete)//resetaza totul
	{
		logicaDelete();
		esteApasatDelete = false;
	}
	if (seCitesteExpresie)
	{
		citireExpresie(event);
		modificareLungimeSimbol(desktop, nodDeGasit->date);
		if (nodDeGasit != nullptr)
			nodDeGasit->date.expresie = expresieDeCitit;
	}
	if (seCitestePtParcurgere())
	{
		citireExpresie(event);
		seCitesteParcurgere = true;
	}
	if (seCitestePtSalvare)
	{
		citireExpresie(event);
	}
	if (esteApasatEnter)//stop citire expresie
	{
		esteApasatEnter = false;
		if (seCitesteParcurgere)
		{
			logicaEnterParcurgere(seCitesteParcurgere, esteApasatF1);
		}
		else if (seCitestePtSalvare)
		{
			logicaEnterSalvare(seCitestePtSalvare);
		}
		else {
			logicaEnter(seCitesteExpresie, nodDeGasit);
		}
		expresieDeCitit.clear();
	}
}
