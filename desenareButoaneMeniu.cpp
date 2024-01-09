#include "desenareButoaneMeniu.h"

void butonSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(desktop.width / 100, desktop.height / 100);
	rectangle.setFillColor(sf::Color(0, 205, 205));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(0, 0, 204));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(desktop.width / 17, desktop.height / 27);
	fereastraAplicatie.draw(mainText);

}

void butonIncarcare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(12 * desktop.width / 100, desktop.height / 100);
	rectangle.setFillColor(sf::Color(0, 205, 205));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(0, 0, 204));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Incarcare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(17 * desktop.width / 100, desktop.height / 27);
	fereastraAplicatie.draw(mainText);

}

void butonStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 8 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(209, 31, 120));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 12 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(204, 0, 102));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(250, 150, 100));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Stop", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(28 * desktop.width / 100, 14 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}

void butonCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 16 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(209, 31, 120));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 20 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(204, 0, 102));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 24 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(209, 31, 120));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 28 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(204, 0, 102));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, 32 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(209, 31, 120));
	rectangle.setOutlineThickness(desktop.width / 350);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(78 * desktop.width / 100, desktop.height / 100);
	rectangle.setFillColor(sf::Color(255, 255, 0));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(239, 255, 0));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Convertire C++", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(83 * desktop.width / 100, desktop.height / 27);
	fereastraAplicatie.draw(mainText);
}

void butonSalvareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 16;
	const int inaltimeButon = desktop.height / 18;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(71 * desktop.width / 100, 12 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(0, 205, 205));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(0, 0, 204));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(74 * desktop.width / 100, 14 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}

void butonRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(89 * desktop.width / 100, desktop.height / 100);
	rectangle.setFillColor(sf::Color(255, 255, 0));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(239, 255, 0));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Rularea codului", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(94 * desktop.width / 100, desktop.height / 27);
	fereastraAplicatie.draw(mainText);
}

void butonRulareTotal(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(89 * desktop.width / 100, 8 * desktop.height / 100);
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
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 25;
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
	const int lungimeButon = desktop.width / 40;
	const int inaltimeButon = desktop.width / 40;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(96 * desktop.width / 100, 87 * desktop.height / 100);
	rectangle.setFillColor(sf::Color(240, 138, 138));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(150, 80, 80));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("?", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(97.25 * desktop.width / 100, 88.75 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}

void butonDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 10;
	const int inaltimeButon = desktop.height / 15;
	sf::RectangleShape rectangle(sf::Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(23 * desktop.width / 100, desktop.height / 100);
	rectangle.setFillColor(sf::Color(204, 0, 102));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(sf::Color(250, 150, 100));
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Instructiuni", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin((marginiText.left) + marginiText.width / 2, (marginiText.top + marginiText.height) / 2);
	mainText.setPosition(28 * desktop.width / 100, desktop.height / 27);
	fereastraAplicatie.draw(mainText);
}

void desenareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
	{
		butonStart(fereastraAplicatie, desktop);
		butonStop(fereastraAplicatie, desktop);
		butonCitire(fereastraAplicatie, desktop);
		butonAfisare(fereastraAplicatie, desktop);
		butonAtribuire(fereastraAplicatie, desktop);
		butonDaca(fereastraAplicatie, desktop);
	}
}
void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungime = 60 * desktop.width / 100;
	const int inaltime = 72 * desktop.height / 100;
	RectangleShape rectangle(Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * desktop.width / 100, 10 * desktop.height / 100);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(Color(0, 0, 0));
	rectangle.setFillColor(Color(255, 255, 255));
	fereastraAplicatie.draw(rectangle);

	butonSalvareConvertire(fereastraAplicatie, desktop);
}

void desenareDropDownRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonRulareTotal(fereastraAplicatie, desktop);
	butonRularePas(fereastraAplicatie, desktop);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	float buttonX = 0.91f * desktop.width / 100;
	float buttonY = 0.83f * desktop.height / 100;
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);

	RenderWindow newWindow(VideoMode(static_cast<float>(50 * desktop.width / 100), static_cast<float>(50 * desktop.height / 100)), "Ajutor");
	newWindow.setFramerateLimit(60);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Proiect InterSchem\n \n Blocurile se vor muta dupa mouse, daca este apasat butonul din stanga;\n \n Pentru a crea legaturi, se vor trasa cu butonul din dreapta mouse-ului; \n \n Pentru a crea blocuri, se vor apasa tastele 1(START), 2(STOP)\n 3(ATRIBUIRE), 4(CITIRE), 5(AFISARE), \n 6(DECIZIE) sau se vor folosi butoanele din meniu;\n \n Pentru a sterge un bloc si legatura sa, se va apasa ESCAPE\n \n Pentru executarea algoritmului se va folosi F12 \n \n Butonul de salvare va salva schema logica, iar cu cel de incarcare se vor \n incarca scheme logice deja facute", fontGlobal, marimeFont);
	mainText.setFillColor(Color::White);
	mainText.setPosition(desktop.width / 100, desktop.height / 100);

	while (newWindow.isOpen())
	{
		Event event;
		while (newWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				newWindow.close();
			}
		}
		newWindow.clear(Color::Black);
		newWindow.draw(mainText);
		newWindow.display();
	}
}

void butoaneMeniu(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonSalvare(fereastraAplicatie, desktop);
	butonIncarcare(fereastraAplicatie, desktop);
	butonDropDown(fereastraAplicatie, desktop);
	butonRulare(fereastraAplicatie, desktop);
	butonConvertire(fereastraAplicatie, desktop);
	butonAjutor(fereastraAplicatie, desktop);
}