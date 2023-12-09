#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "verificareZonaSimbol.h"

dateNod returneazaPozitieMouse(RenderWindow &window) {
    Vector2i pozitieMouse = Mouse::getPosition(window);
    dateNod nodPePozitieMouse;
    nodPePozitieMouse.x = pozitieMouse.x;
    nodPePozitieMouse.y = pozitieMouse.y;
    return nodPePozitieMouse;
}

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
            return;
        creareSimbol(window, A.radacina->date);
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
            dateNod pozMouse = returneazaPozitieMouse(window);
            nod* nodDeSters = gasesteNodInArbore(A, pozMouse);

            if (nodDeSters != nullptr) {
                cout << "Stergere nod de tipul " << nodDeSters->date.tip << " de pe coordonatele (" << nodDeSters->date.x << ',' << nodDeSters->date.y << ")" << endl;
                stergereNodFaraSubarbore(A,nodDeSters);
                return;
            }
        }
    }
}

void logicaLegaturaIntreSimboluri(RenderWindow& window, dateNod dateNod1, dateNod dateNod2) {
    if (!Mouse::isButtonPressed(sf::Mouse::Left))
        return;

    nod* nod1 = nullptr;
    nod* nod2 = nullptr;

    if (listaArbori.empty())
        return;

    for (auto& A : listaArbori) {
        nod* nodGasit = gasesteNodInArbore(A, dateNod1);
        if (nodGasit != nullptr) {
            nod1 = nodGasit;
            break;
        }
    }

    if (dateNod2.tip == -1) {
        Vector2i pozitieMouse = Mouse::getPosition(window);
        dateNod nodPePozitieMouse;
        nodPePozitieMouse.x = pozitieMouse.x;
        nodPePozitieMouse.y = pozitieMouse.y;

        for (auto& A : listaArbori) {
            nod* nodGasit = gasesteNodInArbore(A, nodPePozitieMouse);
            if (nodGasit != nullptr) {
                nod2 = nodGasit;
                break;
            }
        }
    }
}