#include "functiiNod.h"
#include "verificareZonaSimbol.h"
#include <math.h>

bool verificareTemporara(Vector2i pozitieMouse, dateNod date, int distMax) {
    return (sqrt(pow(pozitieMouse.x - date.x, 2) + pow(pozitieMouse.y - date.y, 2)) <= distMax);
}

bool verificareSimbolStart(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolStop(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolAtribuire(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolCitire(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolAfisare(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolDaca(Vector2i pozitieMouse, dateNod date) {
    return false;
}

bool verificareSimbolInZona(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 50);

    switch (date.tip) {
    case 0:
        verificareSimbolStart(pozitieMouse, date); break;
    case 1:
        verificareSimbolStop(pozitieMouse, date); break;
    case 2:
        verificareSimbolAtribuire(pozitieMouse, date); break;
    case 3:
        verificareSimbolCitire(pozitieMouse, date); break;
    case 4:
        verificareSimbolAfisare(pozitieMouse, date); break;
    case 5:
        verificareSimbolDaca(pozitieMouse, date); break;
    }
}