#include "citireExpresie.h"
#include "fereastra.h"
///string s;
string citire(sf:: RenderWindow& window)
{
    string s;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Eroare la incarcarea fontului.\n";
    }
    sf::Text text("", font, 24);
    text.setFillColor(sf::Color::Black);
    
        sf::Event event;  // Move the declaration inside the event loop
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) 
                    window.close();
                else
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) {
                        text.setString(text.getString() + static_cast<char>(event.text.unicode));
                        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                    }
                    else if (event.text.unicode == 8 && !text.getString().isEmpty()) {
                        std::string s = text.getString();
                        s.pop_back();
                        text.setString(s);
                    }
                }
            }
        }
    ///window.draw(text);
    return s;
}