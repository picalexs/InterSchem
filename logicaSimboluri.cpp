#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include "verificareZonaSimbol.h"

void logicaCreareSimbol(RenderWindow& window, map<Keyboard::Key, bool>& esteTastaApasata) {

    for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++) {
        if (Keyboard::isKeyPressed(Keyboard::Key(key))) {
            if (!esteTastaApasata[Keyboard::Key(key)]) {
                cout << "Creare nod: " << key - Keyboard::Num1 << endl;

                Vector2i pozitieMouse = Mouse::getPosition(window);
                dateNod date = schimbareDate(key - Keyboard::Num1, "expresie de test", pozitieMouse.x, pozitieMouse.y);
                arbore ArboreNou;
                atribuireArbore(ArboreNou, date);
                listaArbori.push_back(ArboreNou);

                esteTastaApasata[Keyboard::Key(key)] = true;
            }
        }
        else {
            esteTastaApasata[Keyboard::Key(key)] = false;
        }
    }

    if (listaArbori.empty())
        return;
    for (arbore A : listaArbori) {
        if (A.radacina == nullptr)
            continue;
        creareSimbol(window, A.radacina->date);
    }
}

vector<pair<dateNod, dateNod>> listaLinii;

void stergereLinie(nod *N) {
    for (auto it = listaLinii.begin(); it != listaLinii.end();) {
        if ((it->first.x == N->date.x && it->first.x== N->date.y)||
            (it->second.x == N->date.x && it->second.x == N->date.y)) {
            it = listaLinii.erase(it);
        }
        else {
            ++it;
        }
    }
}

void logicaStergereSimbol(RenderWindow& window, bool& esteApasatStergere) {
    if (!Keyboard::isKeyPressed(Keyboard::Escape) && esteApasatStergere) {
        esteApasatStergere = false;
        return;
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape) && !esteApasatStergere) {
        esteApasatStergere = true;
        // Parcurgerea listei de arbori si a fiecarui arbore pentru a gasi nodul si a-l sterge daca este gasit
        for (auto& A : listaArbori) {
            nod* nodDeSters = gasesteNodCuPozMouse(window , A);

            if (nodDeSters != nullptr) {
                cout << "Stergere nod de tipul " << nodDeSters->date.tip << " de pe coordonatele (" << nodDeSters->date.x << ',' << nodDeSters->date.y << ")" << endl;
                stergereLinie(nodDeSters);
                stergereNodFaraSubarbore(A,nodDeSters);
                return;
            }
        }
    }
}

nod* nod1 = nullptr;
nod* nod2 = nullptr;

void logicaLegaturaIntreSimboluri(RenderWindow& window) {
    desenareLinieIntreSimboluri(window, listaLinii);
    if (Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (nod1 == nullptr) {
            nod1 = gasesteNodListaCuPozMouse(window);
        }
        nod* nod2Nou= gasesteNodListaCuPozMouse(window);
        if (nod2 == nullptr || nod2 == nod1 || nod2Nou!=nod2) {
            nod2 = nod2Nou;
        }
        return;
    }
    if (nod1 == nod2 || nod1 == nullptr || nod2 == nullptr)
        return;

    //nod1->st = nod2;

    Vector2i pozitieMouse = Mouse::getPosition(window);
    /*for(auto it = listaLinii.begin(); it != listaLinii.end();it++)
        if((it->first.x != nod1->date.x && it->first.x != nod1->date.y) &&
            (it->second.x != nod2->date.x && it->second.x != nod2->date.y))*/
    listaLinii.push_back(make_pair(nod1->date, nod2->date));
    nod1 = nullptr; nod2 = nullptr;
}