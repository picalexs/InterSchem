#include "creareSimboluri.h"
#include "desenareSimboluri.h"
using namespace std;

void creareSimbolStart(RenderWindow& window, const dateNod& date) {
    desenareNodStart(window,date);
}

void creareSimbolStop(RenderWindow& window, const dateNod& date) {
    desenareNodStop(window,date);
}

void creareSimbolAtribuire(RenderWindow& window, const dateNod& date) {
	desenareNodAtribuire(window, date);
}

void creareSimbolCitire(RenderWindow& window, const dateNod& date) {
	desenareNodCitire(window, date);
}

void creareSimbolAfisare(RenderWindow& window, const dateNod& date) {
	desenareNodAfisare(window, date);
}

void creareSimbolDaca(RenderWindow& window, const dateNod& date) {
	desenareNodDaca(window, date);
}

void creareSimbol(RenderWindow& window, const dateNod& date) {
    switch (date.tip) {
    case 0:
        creareSimbolStart(window, date); break;
    case 1:
        creareSimbolStop(window, date); break;
    case 2:
        creareSimbolAtribuire(window, date); break;
    case 3:
        creareSimbolCitire(window, date); break;
    case 4:
        creareSimbolAfisare(window, date); break;
    case 5:
        creareSimbolDaca(window, date); break;
    default: 
        return;
    }
}

void creareSimbolPtArboreRecursiv(RenderWindow& window, const nod* N, unordered_set<const nod*>& noduriVizitate) {
	if (N == nullptr || noduriVizitate.count(N)) {
		return;
	}
	noduriVizitate.insert(N);
	creareSimbol(window, N->date);
	creareSimbolPtArboreRecursiv(window, N->st, noduriVizitate);
	creareSimbolPtArboreRecursiv(window, N->dr, noduriVizitate);
}

void creareSimbolPtArbore(RenderWindow& window, const nod* N) {
	unordered_set<const nod*> noduriVizitate;
	creareSimbolPtArboreRecursiv(window, N, noduriVizitate);
}

void creareSimbolPtListaArbori(RenderWindow& window) {
	for (const auto& A : listaArbori)
	{
		if (A.radacina == nullptr)
			continue;
		creareSimbolPtArbore(window, A.radacina);
	}
}