#include "creareSimboluri.h"
#include "desenareSimboluri.h"
using namespace std;

void creareSimbolStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodStart(fereastraAplicatie, desktop, date);
}

void creareSimbolStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodStop(fereastraAplicatie, desktop, date);
}

void creareSimbolAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodAtribuire(fereastraAplicatie, desktop, date);
}

void creareSimbolCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodCitire(fereastraAplicatie, desktop, date);
}

void creareSimbolAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodAfisare(fereastraAplicatie, desktop, date);
}

void creareSimbolDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	desenareNodDaca(fereastraAplicatie, desktop, date);
}

void creareSimbol(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const DateNod& date) {
	switch (date.tip) {
	case 0:
		creareSimbolStart(fereastraAplicatie, desktop, date); break;
	case 1:
		creareSimbolStop(fereastraAplicatie, desktop, date); break;
	case 2:
		creareSimbolAtribuire(fereastraAplicatie, desktop, date); break;
	case 3:
		creareSimbolCitire(fereastraAplicatie, desktop, date); break;
	case 4:
		creareSimbolAfisare(fereastraAplicatie, desktop, date); break;
	case 5:
		creareSimbolDaca(fereastraAplicatie, desktop, date); break;
	default:
		return;
	}
}

void creareSimbolPtArboreRecursiv(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Nod* N, unordered_set<const Nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N)) {
		return;
	}
	noduriVizitate.insert(N);
	creareSimbol(fereastraAplicatie, desktop, N->date);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, N->st, noduriVizitate);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, N->dr, noduriVizitate);
}

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Nod* N) {
	unordered_set<const Nod*> noduriVizitate;
	creareSimbolPtArboreRecursiv(fereastraAplicatie, desktop, N, noduriVizitate);
}

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie, const VideoMode& desktop) {
	for (const auto& A : listaArbori)
	{
		if (A.radacina == nullptr)
			continue;
		creareSimbolPtArbore(fereastraAplicatie, desktop, A.radacina);
	}
}