#include "creareSimboluri.h"
#include "desenareSimboluri.h"
#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;

void creareSimbolStart(dateNod date) {
    desenareNodStart(date);
}

void creareSimbolStop(dateNod date) {
    desenareNodStop(date);
}

void creareSimbolAtribuire(dateNod date) {
    desenareNodAtribuire(date);
}

void creareSimbolCitire(dateNod date) {
    desenareNodCitire(date);
}

void creareSimbolAfisare(dateNod date) {
    desenareNodAfisare(date);
}

void creareSimbolDaca(dateNod date) {
    desenareNodDaca(date);
}

void creareSimbol() {
    map<Keyboard::Key, bool> esteTastaApasata;
    arbore A;
    initializareArbore(A);

    while (!Keyboard::isKeyPressed(Keyboard::Escape)) {
        for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++) {
            if (Keyboard::isKeyPressed(Keyboard::Key(key))) {
                if (!esteTastaApasata[Keyboard::Key(key)]) {
                    cout << "Creare nod: " << key - Keyboard::Num0 << endl;

                    dateNod date = schimbareDate(key - 1, "", 0, 0);

                    if (esteArboreNull(A))
                        A= *creareArbore(date);
                    switch (key) {
                    case 1:
                        creareSimbolStart(date); break;
                    case 2:
                        creareSimbolStop(date); break;
                    case 3:
                        creareSimbolAtribuire(date); break;
                    case 4:
                        creareSimbolCitire(date); break;
                    case 5:
                        creareSimbolAfisare(date); break;
                    case 6:
                        creareSimbolDaca(date); break;
                    }
                    esteTastaApasata[Keyboard::Key(key)] = true;
                }
            }
            else {
                esteTastaApasata[Keyboard::Key(key)] = false;
            }
        }
    }
};