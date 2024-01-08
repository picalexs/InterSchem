#include "functiiNod.h"

DateNod schimbareDate(const TipNod tip, const string& expresie, const float x, const float y, const float lungimeSimbol, const float inaltimeSimbol) {
	DateNod date;
	date.tip = tip;
	date.expresie = expresie;
	date.x = x;
	date.y = y;
	date.lungimeSimbol = lungimeSimbol;
	date.inaltimeSimbol = inaltimeSimbol;
	return date;
}

void initializareNod(Nod& N) {
	schimbareDate(TipNod::NEDEFINIT, "", 0, 0, 0, 0);
	N.st = nullptr; N.dr = nullptr;
}

void atribuireNod(Nod& N, const DateNod& date) {
	N.date = schimbareDate(date.tip, date.expresie, date.x, date.y, date.lungimeSimbol, date.inaltimeSimbol);
	N.st = nullptr; N.dr = nullptr;
}

bool esteNodNull(const Nod* N) {
	return (N == nullptr);
}

Nod* creareNodNull() {
	const auto N = new Nod;
	initializareNod(*N);
	return N;
}

Nod* creareNod(const DateNod& date) {
	const auto N = new Nod;
	atribuireNod(*N, date);
	return N;
}

void inserareFiu(Nod* tata, const bool fiu, const DateNod& date) {
	if (esteNodNull(tata))
		return;
	Nod* N = creareNod(date);
	if (fiu == 0) {//bool fiu: 0-fiu st., 1-fiu dr.
		tata->st = N;
	}
	else {
		tata->dr = N;
	}
}

void initializareArbore(Arbore& A) {
	A.radacina = nullptr;
	A.nrNoduri = 0;
}

void atribuireArbore(Arbore& A, const DateNod& date) {
	Nod* radacinaNoua = creareNod(date);
	A.radacina = radacinaNoua;
	A.nrNoduri = 1;
}

bool esteArboreNull(const Arbore& A) {
	return (A.radacina == nullptr);
}

bool esteNodInArboreRec(Nod* nodCautat, const Nod* radacina, set<const Nod*> noduriVizitate)
{
	if (radacina == nullptr || noduriVizitate.count(radacina))
		return false;
	if (radacina == nodCautat)
		return true;
	noduriVizitate.insert(radacina);
	return (esteNodInArboreRec(nodCautat, radacina->st, noduriVizitate) || esteNodInArboreRec(nodCautat, radacina->dr, noduriVizitate));
}

bool esteNodInArbore(Nod* nodCautat, const Nod* radacina) {
	const set<const Nod*> noduriVizitate;
	return esteNodInArboreRec(nodCautat, radacina, noduriVizitate);
}

bool verificareSimbolInZona(const Vector2f& pozitieMouse, const DateNod& date) {
	return (abs(date.x - pozitieMouse.x) <= date.lungimeSimbol / 2 && abs(date.y - pozitieMouse.y) <= date.inaltimeSimbol / 2);
}

Nod* gasesteNodRec(Nod* nodCurent, const DateNod& date, set<const Nod*> noduriVizitate) {
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent))
		return nullptr;
	if (verificareSimbolInZona({ date.x , date.y }, nodCurent->date))
		return nodCurent;

	noduriVizitate.insert(nodCurent);
	Nod* nodGasit = gasesteNodRec(nodCurent->st, date, noduriVizitate);
	if (nodGasit != nullptr)
		return nodGasit;
	return gasesteNodRec(nodCurent->dr, date, noduriVizitate);
}

Nod* gasesteNod(Nod* nodCurent, const DateNod& date) {
	const set<const Nod*> noduriVizitate;
	return gasesteNodRec(nodCurent, date, noduriVizitate);
}

Nod* gasesteNodInArbore(const Arbore& A, const DateNod& date) {
	if (A.radacina == nullptr)
		return nullptr;
	return gasesteNod(A.radacina, date);
}

Nod* gasesteNodCuPozMouse(const RenderWindow& fereastraAplicatie, const Arbore& A) {
	if (A.radacina == nullptr)
		return nullptr;
	DateNod nodPePozitieMouse;
	nodPePozitieMouse.x = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).x;
	nodPePozitieMouse.y = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).y;
	return gasesteNod(A.radacina, nodPePozitieMouse);
}

Nod* gasesteNodListaCuPozMouse(const RenderWindow& fereastraAplicatie) {
	DateNod nodPePozitieMouse;
	nodPePozitieMouse.x = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).x;
	nodPePozitieMouse.y = fereastraAplicatie.mapPixelToCoords(Mouse::getPosition(fereastraAplicatie)).y;

	Nod* nodGasit = nullptr;
	for (int i = listaArbori.size() - 1; i >= 0; --i) {
		nodGasit = gasesteNodInArbore(listaArbori[i], nodPePozitieMouse);
		if (nodGasit != nullptr) {
			return nodGasit;
		}
	}
	return nodGasit;
}

Nod* gasesteNodInListaArbori(const DateNod& date) {
	for (const auto A : listaArbori)
	{
		Nod* nodGasit = gasesteNodInArbore(A, date);
		if (nodGasit != nullptr)
			return nodGasit;
	}
	return nullptr;
}

Nod* gasesteNodLegatDeWhileRec(Nod* nodCurent, Nod* nodWhile, set<const Nod*>& noduriVizitate)
{
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent))
		return nullptr;
	if (nodCurent->st == nodWhile || nodCurent->dr == nodWhile)
		return nodCurent;
	noduriVizitate.insert(nodCurent);
	Nod* nodGasit = gasesteNodLegatDeWhileRec(nodCurent->st, nodWhile, noduriVizitate);
	if (nodGasit != nullptr)
		return nodGasit;
	return gasesteNodLegatDeWhileRec(nodCurent->dr, nodWhile, noduriVizitate);
}

Nod* gasesteNodLegatDeWhile(Nod* nodWhile)
{
	if (nodWhile == nullptr)
		return nullptr;
	set<const Nod*> noduriVizitate;
	Nod* rezultat = gasesteNodLegatDeWhileRec(nodWhile->st, nodWhile, noduriVizitate);
	if (rezultat == nullptr)
		rezultat = gasesteNodLegatDeWhileRec(nodWhile->dr, nodWhile, noduriVizitate);
	return  rezultat;
}

int numarNoduriMapRecursiv(const Nod* N, set<const Nod*>& noduriVizitate, const map<const Nod*, unsigned int>& noduriParcurse) {
	if (N == nullptr || noduriParcurse.find(N) != noduriParcurse.end() || noduriVizitate.count(N))
		return 0;
	noduriVizitate.insert(N);
	return 1 + numarNoduriMapRecursiv(N->st, noduriVizitate, noduriParcurse) + numarNoduriMapRecursiv(N->dr, noduriVizitate, noduriParcurse);
}

int numarNoduriMap(const Nod* N, const map<const Nod*, unsigned int>& noduriParcurse) {
	if (N == nullptr)
		return 0;
	set<const Nod*> noduriVizitate;
	return numarNoduriMapRecursiv(N, noduriVizitate, noduriParcurse);
}

int numarNoduriRecursiv(const Nod* N, set<const Nod*>& noduriVizitate)
{
	if (N == nullptr || noduriVizitate.count(N))
		return 0;
	noduriVizitate.insert(N);
	return 1 + numarNoduriRecursiv(N->st, noduriVizitate) + numarNoduriRecursiv(N->dr, noduriVizitate);
}

int numarNoduri(const Nod* N) {
	if (N == nullptr)
		return 0;
	set<const Nod*> noduriVizitate;
	return numarNoduriRecursiv(N, noduriVizitate);
}

int numarNoduriDinArbore(const Arbore A) {
	if (A.radacina == nullptr)
		return 0;
	return numarNoduri(A.radacina);
}

int numarNoduriDinListaArbori() {
	int nrNoduri = 0;
	for (const auto A : listaArbori)
		nrNoduri += numarNoduriDinArbore(A);
	return nrNoduri;
}

void stergereTotSubNodRec(Nod*& N, set<const Nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N))
		return;

	noduriVizitate.insert(N);
	stergereTotSubNodRec(N->st, noduriVizitate);
	stergereTotSubNodRec(N->dr, noduriVizitate);

	N = nullptr;
	delete N;
}

void stergereTotSubNod(Nod*& N)
{
	if (N == nullptr)
		return;
	set<const Nod*> noduriVizitate;
	stergereTotSubNodRec(N, noduriVizitate);
}

void stergereDinListaArbori(const Nod* N) {
	for (int i = 0; i < listaArbori.size();) {
		if (listaArbori[i].radacina == N) {
			listaArbori.erase(listaArbori.begin() + i);
			break;
		}
		++i;
	}
}

bool esteRadacina(const Nod* N)
{
	for (const auto& A : listaArbori)
	{
		if (A.radacina == N)
			return true;
	}
	return false;
}

//gaseste nodul tata al nodului cautat daca exista legatura intre ei
Nod* gasesteNodTataRec(Nod* N, Nod*& nodCautat, set<const Nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N))
		return nullptr;
	if (N->st == nodCautat || N->dr == nodCautat)
		return N;

	noduriVizitate.insert(N);
	Nod* nodTata = gasesteNodTataRec(N->st, nodCautat, noduriVizitate);
	if (nodTata == nullptr)
		nodTata = gasesteNodTataRec(N->dr, nodCautat, noduriVizitate);

	N = nullptr;
	delete N;
	return nodTata;
}

Nod* gasesteNodTata(Nod* N, Nod*& nodCautat)
{
	set<const Nod*> noduriVizitate;
	return gasesteNodTataRec(N, nodCautat, noduriVizitate);
}

int pozitiaArboreleNodului(Nod* N)
{
	for (int i = 0; i < listaArbori.size(); i++)
	{
		if (esteNodInArbore(N, listaArbori[i].radacina))
			return i;
	}
	return -1;
}

void stergereNod(Nod* N) {
	if (N == nullptr)
		return;
	Nod* subarbore1 = N->st;
	Nod* subarbore2 = N->dr;

	if (esteRadacina(N))
	{
		stergereDinListaArbori(N);
	}
	else
	{
		Nod* nodTata = nullptr;
		int poz = -1;
		for (int i = 0; i < listaArbori.size(); i++)
		{
			nodTata = gasesteNodTata(listaArbori[i].radacina, N);
			if (nodTata != nullptr) {
				poz = i;
				break;
			}
		}
		if (nodTata != nullptr) {
			if (nodTata->st == N)
				nodTata->st = nullptr;
			else
				nodTata->dr = nullptr;
			listaArbori[poz].nrNoduri -= numarNoduri(N);
		}
	}
	N->st = nullptr;
	N->dr = nullptr;

	if (subarbore1 != nullptr)
	{
		listaArbori.push_back(Arbore{ subarbore1, numarNoduri(subarbore1) });
	}
	if (subarbore2 != nullptr)
	{
		listaArbori.push_back(Arbore{ subarbore2, numarNoduri(subarbore2) });
	}
	stergereTotSubNod(N);
}

void seteazaVariabila(const string& nume, const long double valoare) {
	variabile[nume] = valoare;
}

long double obtineValDupaNume(const string& nume) {
	const auto it = variabile.find(nume);
	if (it != variabile.end()) {
		return it->second;
	}
	else {
		cout << "Variabila \"" << nume << "\" nu a fost gasita.\n";
		return NAN;
	}
}

bool esteVariabila(const string& token) {
	return variabile.find(token) != variabile.end();
}

void atribuireConstanteCunoscute()
{
	seteazaVariabila("PI", 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899L);
	seteazaVariabila("e", 2.718281828459045235360287471352662497757247093699959574966967627724076630353L);
	seteazaVariabila("g", 9.80665f);
	seteazaVariabila("phi", 1.61803398874989484820458683436563811772030917980576286213544862270526046281890L);
}