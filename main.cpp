#include <SFML/Graphics.hpp>
#include "structs.h"
#include "functiiNod.h"
#include <cstdlib>
#include <ctime>

void deseneazaArbore(sf::RenderWindow& window, nod* nodCurent, float x, float y, float spacing) {
    if (nodCurent == nullptr) {
        return;
    }

    // Desenează legătura către fiul stâng, dacă există
    if (nodCurent->st != nullptr) {
        float childX = x - spacing;
        float childY = y + 100.f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y + 20.f), sf::Color::Black),  // Schimbarea culorii în negru pentru linie
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::Black) // Schimbarea culorii în negru pentru linie
        };
        window.draw(line, 2, sf::Lines);
        deseneazaArbore(window, nodCurent->st, childX, childY, spacing * 0.5f);
    }

    // Desenează legătura către fiul drept, dacă există
    if (nodCurent->dr != nullptr) {
        float childX = x + spacing;
        float childY = y + 100.f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y + 20.f), sf::Color::Black),  // Schimbarea culorii în negru pentru linie
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::Black) // Schimbarea culorii în negru pentru linie
        };
        window.draw(line, 2, sf::Lines);
        deseneazaArbore(window, nodCurent->dr, childX, childY, spacing * 0.5f);
    }

    // Desenează nodul curent
    sf::CircleShape nodeShape(20.f);
    nodeShape.setFillColor(sf::Color::Blue);
    nodeShape.setPosition(x, y);
    window.draw(nodeShape);

    // Afișează numele nodului
    sf::Font font;
    font.loadFromFile("Arial.ttf"); // Înlocuiește cu calea către fontul dorit
    sf::Text text(numeNoduri[nodCurent->date.tip], font, 16);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 20.f, y - 30.f); // Ajustează poziția textului
    window.draw(text);
}


void adaugaNoduri(nod* nodCurent, int numarNoduri, int& contor, int nivel) {
    if (contor >= numarNoduri || nivel >= 4) { // Assuming a maximum depth of 4 for the tree
        return;
    }

    unsigned int seed = static_cast<unsigned int>(std::time(nullptr)); // Seed based on current time
    srand(seed);

    int probabilitate = rand() % 100;
    if (nodCurent->date.tip == 0) {
        // If it's the Start node, add an If, Citire, or Afisare node
        if (probabilitate < 33) {
            nodCurent->st = creareNod({ 5, "ExpresieIf", 0, 0 });
        }
        else if (probabilitate >= 33 && probabilitate < 66) {
            nodCurent->st = creareNod({ 3, "ExpresieCitire", 0, 0 });
        }
        else {
            nodCurent->st = creareNod({ 4, "ExpresieAfisare", 0, 0 });
        }
        contor++;
        adaugaNoduri(nodCurent->st, numarNoduri, contor, nivel + 1);
    }
    else if (nodCurent->date.tip == 5) {
        // If it's an If node, add an V or C node
        if (probabilitate < 50) {
            nodCurent->st = creareNod({ 2, "ExpresieAtribuire", 0, 0 });
        }
        else {
            nodCurent->st = creareNod({ 1, "ExpresieStop", 0, 0 });
            contor++;
        }
        adaugaNoduri(nodCurent->st, numarNoduri, contor, nivel + 1);
    }
    else if (nodCurent->date.tip == 2) {
        // If it's a V node, add a C or STOP node
        if (probabilitate < 50) {
            nodCurent->st = creareNod({ 3, "ExpresieCitire", 0, 0 });
        }
        else {
            nodCurent->st = creareNod({ 1, "ExpresieStop", 0, 0 });
            contor++;
        }
        adaugaNoduri(nodCurent->st, numarNoduri, contor, nivel + 1);
    }

    probabilitate = rand() % 100;
    if (probabilitate < 50) {
        nodCurent->dr = creareNod({ 1, "ExpresieStop", 0, 0 }); // The leaf nodes are always STOP
        contor++;
    }

    // Recursively add nodes to the right side
    if (nodCurent->dr != nullptr && contor < numarNoduri) {
        adaugaNoduri(nodCurent->dr, numarNoduri, contor, nivel);
    }
}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arbore");
    window.setFramerateLimit(45);
    srand(static_cast<unsigned int>(time(nullptr)));

    arbore* A = creareArbore({ 0, "Expresie", 400, 50 });
    int contor = 0;
    adaugaNoduri(A->radacina, 6, contor,0);

    while (window.isOpen()) {
        sf::Event event;
        srand(static_cast<unsigned int>(std::time(nullptr))); // Inițializare seed pentru numere aleatoare înainte de bucla principală
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                stergereNod(A->radacina);
                A->radacina = nullptr;
                A->nrNoduri = 0;
                A = creareArbore({ 0, "Expresie", 400, 50 });
                contor = 0;
                adaugaNoduri(A->radacina, 6, contor,0);
            }
        }

        window.clear(sf::Color::White);

        if (!esteArboreNull(*A)) {
            deseneazaArbore(window, A->radacina, 400.f, 50.f, 200.f);
        }

        window.display();
    }

    return 0;
}
