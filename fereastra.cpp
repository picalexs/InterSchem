#include "testareArbore.h"
#include "logicaSimboluri.h"

void creareFereastra() {

    RenderWindow window(VideoMode(1000, 800), "Interschem");
    window.setFramerateLimit(45);

    map<Keyboard::Key, bool> esteTastaApasata;
    bool esteApasatStergere = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        logicaCreareSimbol(window, esteTastaApasata);
        logicaStergereSimbol(window, esteApasatStergere);

        window.display();
    }
}