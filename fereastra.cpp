#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "testareArbore.h"
#include "creareSimboluri.h"
#include "functiiNod.h"
#include "verificareZonaSimbol.h"
using namespace sf;

void logicaCreareSimbol(RenderWindow& window, arbore A, dateNod date,
    map<Keyboard::Key, bool> &esteTastaApasata, vector<dateNod> &dateSimboluriIzolate) {

    for (int key = Keyboard::Num1; key <= Keyboard::Num6; key++) {
        if (Keyboard::isKeyPressed(Keyboard::Key(key))) {
            if (!esteTastaApasata[Keyboard::Key(key)]) {
                cout << "Creare nod: " << key - Keyboard::Num1 << endl;

                Vector2i pozitieMouse = Mouse::getPosition(window);
                date = schimbareDate(key - Keyboard::Num1, "expresie de test", pozitieMouse.x, pozitieMouse.y);
                dateSimboluriIzolate.push_back(date);

                if (esteArboreNull(A))
                    A = *creareArbore(date);

                esteTastaApasata[Keyboard::Key(key)] = true;
            }
        }
        else {
            esteTastaApasata[Keyboard::Key(key)] = false;
        }
    }

    for (dateNod dateSimbol: dateSimboluriIzolate)
        creareSimbol(window, dateSimbol);
}

void logicaStergereSimbol(RenderWindow& window, dateNod date, bool& esteApasatStergere, vector<dateNod>& dateSimboluriIzolate) {
    if (!Keyboard::isKeyPressed(Keyboard::Escape) && esteApasatStergere) {
        esteApasatStergere = false;
        return;
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape) && !esteApasatStergere) {
        esteApasatStergere = true;
        // Parcurgerea vectorului de noduri izolate si stergerea simbolului daca este gasit
        for (auto it = dateSimboluriIzolate.begin(); it != dateSimboluriIzolate.end();) {
            if (verificareSimbolInZona(Mouse::getPosition(window), *it)) {
                cout << "Stergere nod de tipul " << it->tip << " de pe coordonatele (" << it->x << ',' << it->y << ")" << endl;
                it = dateSimboluriIzolate.erase(it);
                return;
            }
            else {
                ++it;
            }
        }
    }
}

void testare(RenderWindow& window, dateNod date) {

    CircleShape triangle;
    triangle.setRadius(50);
    triangle.setPointCount(3);
    window.draw(triangle);
    triangle.setPosition(100, 200);
    triangle.setFillColor(Color::Black);
    window.draw(triangle);
    ///line.rotate(45);
    //desenare nod start ca elipsa folosind date.x, date.y si eventual o raza sau poate un colt st, colt dr

}

void creareFereastra() {

    RenderWindow window(VideoMode(1000, 800), "Interschem");
    window.setFramerateLimit(45);

    map<Keyboard::Key, bool> esteTastaApasata;
    bool esteApasatStergere = false;
    arbore A;
    initializareArbore(A);
    dateNod date;
    vector<dateNod> dateSimboluriIzolate;//Trebuie eventual schimbat fisierul in care se salveaza


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        window.clear(sf::Color::White);

        logicaCreareSimbol(window, A, date, esteTastaApasata, dateSimboluriIzolate);
        logicaStergereSimbol(window, date,esteApasatStergere, dateSimboluriIzolate);

        ///testare(window, date);

        window.display();
    }
}