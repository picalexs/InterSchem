#include "creareSimboluri.h"
#include "desenareSimboluri.h"
using namespace std;

void creareSimbolStart(RenderWindow& window, const Font& font, const dateNod& date) {
    desenareNodStart(window, font,date);
}

void creareSimbolStop(RenderWindow& window,const Font &font, const dateNod& date) {
    desenareNodStop(window,font,date);
}

void creareSimbolAtribuire(RenderWindow& window, const dateNod& date) {
    desenareNodAtribuire(window, date);
}

void creareSimbolCitire(RenderWindow& window, const dateNod& date) {
    desenareNodCitire(window,date);
}

void creareSimbolAfisare(RenderWindow& window, const dateNod& date) {
    desenareNodAfisare(window,date);
}

void creareSimbolDaca(RenderWindow& window, const dateNod& date) {
    desenareNodDaca(window,date);
}

void creareSimbol(RenderWindow& window, const Font& font, const dateNod& date) {
    switch (date.tip) {
    case 0:
        creareSimbolStart(window, font, date); break;
    case 1:
        creareSimbolStop(window,font, date); break;
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

void creareSimbolPtArbore(RenderWindow& window, const Font& font, const nod *N) {
    if (N == nullptr)
        return;
    creareSimbol(window,font, N->date);
    creareSimbolPtArbore(window,font, N->st);
    creareSimbolPtArbore(window,font, N->dr);
}

void creareSimbolPtListaArbori(RenderWindow& window, const Font& font) {
    for (const auto& A : listaArbori)
    {
        if (A.radacina == nullptr)
            continue;
        creareSimbolPtArbore(window,font, A.radacina);
    }
}