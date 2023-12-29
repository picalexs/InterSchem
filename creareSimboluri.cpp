#include "creareSimboluri.h"
#include "desenareSimboluri.h"
using namespace std;

void creareSimbolStart(RenderWindow& fereastraAplicatie,const dateNod& date) {
    desenareNodStart(fereastraAplicatie, date);
}

void creareSimbolStop(RenderWindow& fereastraAplicatie,const dateNod& date) {
    desenareNodStop(fereastraAplicatie, date);
}

void creareSimbolAtribuire(RenderWindow& fereastraAplicatie,const dateNod& date) {
	desenareNodAtribuire(fereastraAplicatie, date);
}

void creareSimbolCitire(RenderWindow& fereastraAplicatie,const dateNod& date) {
	desenareNodCitire(fereastraAplicatie, date);
}

void creareSimbolAfisare(RenderWindow& fereastraAplicatie,const dateNod& date) {
	desenareNodAfisare(fereastraAplicatie, date);
}

void creareSimbolDaca(RenderWindow& fereastraAplicatie,const dateNod& date) {
	desenareNodDaca(fereastraAplicatie, date);
}

void creareSimbol(RenderWindow& fereastraAplicatie, const dateNod& date) {
	switch (date.tip) {
    case 0:
		creareSimbolStart(fereastraAplicatie, date); break;
    case 1:
        creareSimbolStop(fereastraAplicatie, date); break;
    case 2:
        creareSimbolAtribuire(fereastraAplicatie, date); break;
    case 3:
        creareSimbolCitire(fereastraAplicatie, date); break;
    case 4:
        creareSimbolAfisare(fereastraAplicatie, date); break;
    case 5:
        creareSimbolDaca(fereastraAplicatie, date); break;
    default: 
        return;
    }
}

void creareSimbolPtArboreRecursiv(RenderWindow& fereastraAplicatie, const nod* N, unordered_set<const nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N)) {
		return;
	}
	noduriVizitate.insert(N);
	creareSimbol(fereastraAplicatie, N->date);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, N->st, noduriVizitate);
	creareSimbolPtArboreRecursiv(fereastraAplicatie, N->dr, noduriVizitate);
}

void creareSimbolPtArbore(RenderWindow& fereastraAplicatie, const nod* N) {
	unordered_set<const nod*> noduriVizitate;
	creareSimbolPtArboreRecursiv(fereastraAplicatie, N, noduriVizitate);
}

void creareSimbolPtListaArbori(RenderWindow& fereastraAplicatie) {
	for (const auto& A : listaArbori)
	{
		if (A.radacina == nullptr)
			continue;
		creareSimbolPtArbore(fereastraAplicatie, A.radacina);
	}
}