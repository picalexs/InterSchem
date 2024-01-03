#include "butoaneMeniu.h"

void butonSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width/10; 
    inaltimeButon = desktop.height/15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(25, 0);
    rectangle.setFillColor(sf::Color(0, 205, 205));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Salvare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(90, 20);
    fereastraAplicatie.draw(mainText);

}

void butonIncarcare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(175, 0);
    rectangle.setFillColor(sf::Color(0, 205, 205));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Incarcare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(240, 20);
    fereastraAplicatie.draw(mainText);

}

void butonStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 20;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(400, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Start", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(435, 20);
    fereastraAplicatie.draw(mainText);
}

void butonStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 20;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(475, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Stop", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(510, 20);
    fereastraAplicatie.draw(mainText);
}

void butonCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 20;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(550, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Citire", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(585, 20);
    fereastraAplicatie.draw(mainText);
}

void butonAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 20;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(625, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Afisare", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(660, 20);
    fereastraAplicatie.draw(mainText);
}

void butonAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 15;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(700, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Atribuire", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(745, 20);
    fereastraAplicatie.draw(mainText);
}

void butonDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 20;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(800, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Daca", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(835, 20);
    fereastraAplicatie.draw(mainText);
}

void butonCatTimp(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 15;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(875, 0);
    rectangle.setFillColor(sf::Color(204, 0, 102));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Cat Timp", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(920, 20);
    fereastraAplicatie.draw(mainText);
}

void butonConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(1050, 0);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Convertire C++", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(1120, 20);
    fereastraAplicatie.draw(mainText);
}

void butonRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 10;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(1200, 0);
    rectangle.setFillColor(sf::Color(255, 255, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Rularea codului", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(1270, 20);
    fereastraAplicatie.draw(mainText);
}

void butonAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
    int lungimeButon, inaltimeButon;
    lungimeButon = desktop.width / 15;
    inaltimeButon = desktop.height / 15;
    sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

    rectangle.setPosition(25, 650);
    rectangle.setFillColor(sf::Color(255, 0, 0));
    fereastraAplicatie.draw(rectangle);

    const int marimeFont = static_cast<int>(desktop.width) / 70;
    Text mainText("Ajutor", fontGlobal, marimeFont);
    mainText.setFillColor(Color::Black);
    const FloatRect marginiText = mainText.getLocalBounds();
    mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
    mainText.setPosition(70, 675);
    fereastraAplicatie.draw(mainText);
}