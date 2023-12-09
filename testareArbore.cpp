#include <SFML/Graphics.hpp>
#include <ctime>
#include "functiiNod.h"
using namespace sf;

void deseneazaArbore(RenderWindow& window, nod* nodCurent, float x, float y, float spacing) {
    if (nodCurent == nullptr) {
        return;
    }

    CircleShape nodeShape(20.f);
    if (nodCurent->date.tip <= 1)
        nodeShape.setFillColor(Color::Black);
    else if (nodCurent->date.tip == 2)
        nodeShape.setFillColor(Color::Yellow);
    else if (nodCurent->date.tip == 3)
        nodeShape.setFillColor(Color::Green);
    else if (nodCurent->date.tip == 4)
        nodeShape.setFillColor(Color::Red);
    else
        nodeShape.setFillColor(Color::Magenta);
    nodeShape.setPosition(x - 20, y - 10);
    window.draw(nodeShape);

    Font font;
    font.loadFromFile("Arial.ttf");
    Text text(numeNoduri[nodCurent->date.tip], font, 16);
    text.setFillColor(Color::Black);
    text.setPosition(x - 20.f, y-30.f);
    window.draw(text);

    float newX = x;
    float newY = y + 75;

    if (nodCurent->st != nullptr && nodCurent->date.tip != 5) {
        Vertex line[] = {
            Vertex(Vector2f(x, y + 28.f), Color::Black),
            Vertex(Vector2f(newX, newY), Color::Black)
        };
        window.draw(line, 2, Lines);
        deseneazaArbore(window, nodCurent->st, newX, newY, spacing);
    }

    newX = x - 2.5f * spacing;
    newY = y + 100.f;

    if (nodCurent->st != nullptr && nodCurent->date.tip == 5) {
        Vertex line[] = {
            Vertex(Vector2f(x, y + 28.f), Color::Black),
            Vertex(Vector2f(newX, newY), Color::Black)
        };
        window.draw(line, 2, Lines);
        deseneazaArbore(window, nodCurent->st, newX, newY, spacing * 0.5f);
    }

    newX = x + 2.5f * spacing;
    if (nodCurent->dr != nullptr && nodCurent->date.tip == 5) {
        Vertex line[] = {
            Vertex(Vector2f(x, y + 28.f), Color::Black),
            Vertex(Vector2f(newX, newY), Color::Black)
        };
        window.draw(line, 2, Lines);
        deseneazaArbore(window, nodCurent->dr, newX, newY, spacing * 0.5f);
    }
}

void adaugaNoduriRandom(nod* nodCurent, int numarNoduri, int& contor, int nivel) {
    if ((contor >= numarNoduri || nivel >= 5) && nodCurent->date.tip != 5) {
        if (nodCurent->st == nullptr && nodCurent->dr == nullptr && nodCurent->date.tip != 1) {
            nodCurent->st = creareNod({ 1, "ExpresieStop", 0, 0 });
            contor++;
        }
        return;
    }
    int probabilitate = rand() % 100;
    if (nodCurent->date.tip == 0 || nodCurent->date.tip == 5) {
        for (int i = 0; i < 2; ++i) {
            int tipNod = rand() % 4 + 2;
            nod* newNode = creareNod({ tipNod, "Expresie" + numeNoduri[tipNod], 0, 0 });
            if (i == 0) {
                nodCurent->st = newNode;
            }
            else {
                nodCurent->dr = newNode;
            }
            adaugaNoduriRandom(newNode, numarNoduri, contor, nivel + 1);
        }
        contor += 2;
    }
    else if (nodCurent->date.tip != 1) {
        int tipNod = rand() % 5 + 1;
        nodCurent->st = creareNod({ tipNod, "Expresie" + numeNoduri[tipNod], 0, 0 });
        adaugaNoduriRandom(nodCurent->st, numarNoduri, contor, nivel + 1);
        contor++;
    }

    if (contor < numarNoduri && nodCurent->st == nullptr && nodCurent->dr == nullptr) {
        if (nodCurent->date.tip != 5 && nodCurent->date.tip != 1) {
            nodCurent->st = creareNod({ 1, "ExpresieStop", 0, 0 });
            contor++;
        }
    }
}

void generareArbore() {
    RenderWindow window(VideoMode(1000, 800), "Arbore");
    window.setFramerateLimit(45);
    srand(time(nullptr));

    arbore* A = creareArbore({ 0, "Expresie", 500, 50 });
    int contor = 0;
    adaugaNoduriRandom(A->radacina, 6, contor, 0);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                stergereIntregArbore(A->radacina);
                A->radacina = nullptr;
                A->nrNoduri = 0;
                A = creareArbore({ 0, "Expresie", 400, 50 });
                contor = 0;
                srand(time(nullptr));
                adaugaNoduriRandom(A->radacina, 6, contor, 0);
            }
        }

        window.clear(Color::White);
        if (!esteArboreNull(*A)) {
            deseneazaArbore(window, A->radacina, 500.f, 50.f, 100.f);
            Font font;
            font.loadFromFile("Arial.ttf");
            Text text("Resetaza arborele cu 'R'.", font, 16);
            text.setFillColor(Color::Black);
            text.setPosition(0, 0);
            window.draw(text);
        }
        window.display();
    }
}