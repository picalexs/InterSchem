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
        logicaLegaturaIntreSimboluri(window);

        Font font;
        font.loadFromFile("Arial.ttf");
        string textDeAfisat = "Nr. simboluri: " + std::to_string(numarNoduriDinListaArbori());
        Text text(textDeAfisat, font, 16);
        text.setFillColor(Color::Black);
        text.setPosition(0, 0);
        window.draw(text);

        window.display();
    }
}