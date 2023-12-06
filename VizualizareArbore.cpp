#include <SFML/Graphics.hpp>
#include "structs.h"
#include "functiiNod.h"

// Funcție recursivă pentru desenarea arborelui
void deseneazaArbore(sf::RenderWindow& window, nod* nodCurent, float x, float y, float spacing) {
    if (nodCurent == nullptr) {
        return;
    }

    // Desenează nodul curent
    sf::CircleShape nodeShape(20.f);
    nodeShape.setFillColor(sf::Color::Blue);
    nodeShape.setPosition(x, y);
    window.draw(nodeShape);

    // Desenează legătura către fiul stâng, dacă există
    if (nodCurent->st != nullptr) {
        float childX = x - spacing;
        float childY = y + 100.f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y + 20.f)),
            sf::Vertex(sf::Vector2f(childX, childY))
        };
        window.draw(line, 2, sf::Lines);
        deseneazaArbore(window, nodCurent->st, childX, childY, spacing * 0.5f);
    }

    // Desenează legătura către fiul drept, dacă există
    if (nodCurent->dr != nullptr) {
        float childX = x + spacing;
        float childY = y + 100.f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 40.f, y + 20.f)),
            sf::Vertex(sf::Vector2f(childX, childY))
        };
        window.draw(line, 2, sf::Lines);
        deseneazaArbore(window, nodCurent->dr, childX, childY, spacing * 0.5f);
    }
}

void testareDesen() {
    // Creează fereastra
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arbore");

    // Crează un arbore de exemplu
    arbore* A = creareArbore({ 'I', "Expresie", 400, 50 });

    // Loop-ul principal pentru desenarea arborelui
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Desenează arborele
        if (!esteArboreNull(*A)) {
            deseneazaArbore(window, A->radacina, 400.f, 50.f, 200.f);
        }

        window.display();
    }
}
