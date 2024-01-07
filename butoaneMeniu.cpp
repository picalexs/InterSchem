#include "butoaneMeniu.h"

void butonSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width/10; 
    inaltimeButon = desktop.height/15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(desktop.width/100, desktop.height/100);
    rectangle.setFillColor(sf::Color(0, 205, 205));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(0, 0, 204));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Salvare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(desktop.width/17, desktop.height/27);
    fereastraAplicatie.draw(mainText);

}

void butonIncarcare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(12*desktop.width/100, desktop.height / 100);
    rectangle.setFillColor(sf::Color(0, 205, 205));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(0, 0, 204));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Incarcare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(17*desktop.width / 100, desktop.height/27);
    fereastraAplicatie.draw(mainText);

}

void butonStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23*desktop.width/100, 8*desktop.height/100);
    rectangle.setFillColor(sf::Color(209, 31, 120));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Start", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 10 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23*desktop.width/100, 12*desktop.height/100);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Stop", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 14*desktop.height/100);
    fereastraAplicatie.draw(mainText);
}

void butonCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23*desktop.width/100, 16*desktop.height/100);
    rectangle.setFillColor(sf::Color(209, 31, 120));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Citire", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 18 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23 * desktop.width / 100, 20 * desktop.height / 100);
    rectangle.setFillColor(sf::Color(204, 0, 102));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Afisare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 22 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23 * desktop.width / 100, 24 * desktop.height / 100);
    rectangle.setFillColor(sf::Color(209, 31, 120));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Atribuire", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 26 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23 * desktop.width / 100, 28 * desktop.height / 100);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Decizie", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 30 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonCatTimp(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23 * desktop.width / 100, 32 * desktop.height / 100);
    rectangle.setFillColor(sf::Color(209, 31, 120));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Cat Timp", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28 * desktop.width / 100, 48 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(78*desktop.width/100, desktop.height / 100);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(239, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Convertire C++", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(83*desktop.width/100, desktop.height/27);
    fereastraAplicatie.draw(mainText);
}

void butonRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(89*desktop.width/100, desktop.height / 100);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(239, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Rularea codului", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(94*desktop.width/100, desktop.height/27);
    fereastraAplicatie.draw(mainText);
}

void butonRulareTotal(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(89 * desktop.width / 100, 8*desktop.height / 100);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    rectangle.setOutlineThickness(desktop.width / 350);
    rectangle.setOutlineColor(sf::Color(239, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Rulare Total", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(94 * desktop.width / 100, 10 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonRularePas(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 25;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(89 * desktop.width / 100, 12 * desktop.height / 100);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    rectangle.setOutlineThickness(desktop.width / 350);
    rectangle.setOutlineColor(sf::Color(239, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Pas cu Pas", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(94 * desktop.width / 100, 14 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 15;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(91*desktop.width/100, 83*desktop.height/100);
    rectangle.setFillColor(sf::Color(255, 0, 0));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(199, 7, 7));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Ajutor", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(94*desktop.width/100, 86 * desktop.height / 100);
    fereastraAplicatie.draw(mainText);
}

void butonDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(23*desktop.width/100, desktop.height/100);
    rectangle.setFillColor(sf::Color(204, 0, 102));
   rectangle.setOutlineThickness(desktop.width/350);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Instructiuni", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(28*desktop.width/100, desktop.height/27);
    fereastraAplicatie.draw(mainText);
}