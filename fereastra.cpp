#include "testareArbore.h"
#include "logicaSimboluri.h"
#include "creareSimboluri.h"
#include "desenareSimboluri.h"

void functieDebugging(RenderWindow & window) {
    Font font;
    font.loadFromFile("Arial.ttf");
    string textSimboluri = "Nr. de simboluri: " + std::to_string(numarNoduriDinListaArbori());
    Text text1(textSimboluri, font, 16);
    text1.setFillColor(Color::Black);
    text1.setPosition(0, 0);
    window.draw(text1);

    string textArbori = "Nr. de elemente din fiecare arbore:";
    for (int i = 0; i < listaArbori.size(); i++)
        textArbori += " " + to_string(numarNoduriDinArbore(listaArbori[i]));
    Text text2(textArbori, font, 16);
    text2.setFillColor(Color::Black);
    text2.setPosition(0, 15);
    window.draw(text2);

    string textLegaturi = ("Nr. de legaturi: " + to_string(listaLinii.size()));
    Text text3(textLegaturi, font, 16);
    text3.setFillColor(Color::Black);
    text3.setPosition(0, 30);
    window.draw(text3);

    Text text4("Resetaza arborele cu 'R'.", font, 16);
    text4.setFillColor(Color::Black);
    text4.setPosition(820, 0);
    window.draw(text4);
}

void creareFereastra() {

    RenderWindow window(VideoMode(1000, 800), "Interschem");
    window.setFramerateLimit(45);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            listaArbori.clear();
            listaLinii.clear();

        }

        window.clear(sf::Color::White);

        logicaCreareSimbol(window);
        logicaStergereSimbol(window);
        logicaLegaturaIntreSimboluri(window);

        creareSimbolPtListaArbori(window);
        desenareLinieIntreSimboluri(window);

        functieDebugging(window);

        window.display();
    }
}