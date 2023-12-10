#include "functiiNod.h"
#include "verificareZonaSimbol.h"
#include <math.h>

bool verificareTemporara(Vector2i pozitieMouse, dateNod date, int distMax) {
    return (sqrt(pow(pozitieMouse.x - date.x, 2) + pow(pozitieMouse.y - date.y, 2)) <= distMax);
}

bool verificareSimbolStart(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolStop(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolAtribuire(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolCitire(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolAfisare(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolDaca(Vector2i pozitieMouse, dateNod date) {
    return verificareTemporara(pozitieMouse, date, 40);
}

bool verificareSimbolInZona(Vector2i pozitieMouse, dateNod date) {
    switch (date.tip) {
    case 0:
        return verificareSimbolStart(pozitieMouse, date);
    case 1:
        return verificareSimbolStop(pozitieMouse, date);
    case 2:
        return verificareSimbolAtribuire(pozitieMouse, date);
    case 3:
        return verificareSimbolCitire(pozitieMouse, date);
    case 4:
        return verificareSimbolAfisare(pozitieMouse, date);
    case 5:
        return verificareSimbolDaca(pozitieMouse, date);
    }
    return false;
}