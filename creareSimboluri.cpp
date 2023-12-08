#include "creareSimboluri.h"
#include "desenareSimboluri.h"
using namespace std;

void creareSimbolStart(RenderWindow& window ,dateNod date) {
    desenareNodStart(window,date);
}

void creareSimbolStop(RenderWindow& window, dateNod date) {
    desenareNodStop(window,date);
}

void creareSimbolAtribuire(RenderWindow& window, dateNod date) {
    desenareNodAtribuire(window,date);
}

void creareSimbolCitire(RenderWindow& window, dateNod date) {
    desenareNodCitire(window,date);
}

void creareSimbolAfisare(RenderWindow& window, dateNod date) {
    desenareNodAfisare(window,date);
}

void creareSimbolDaca(RenderWindow& window, dateNod date) {
    desenareNodDaca(window,date);
}

void creareSimbol(RenderWindow& window, dateNod date) {
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
    }
}