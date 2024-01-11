#include "desenareButoaneMeniu.h"

#include "incarcareDate.h"

float lungimeButonStandard = 0;
float inaltimeButonStandard = 0;
float pozitieXSimbolStandard = 0;
float pozitieYSimbolStandard = 0;
Color culoareOutlineStandard(232, 157, 51);
Color culoareOutlineCreare(145, 15, 40);
Color culoareOutlineCreareSimboluri(212, 42, 75);
Color culoareOutlineRulare(24, 117, 158);
Color culoareOutlineExecutare(33, 138, 184);
Color culoareCreare1(235, 100, 128);
Color culoareCreare2(232, 77, 108);
Color culoareRulare(119, 196, 230);
Color culoareExecutare(161, 208, 230);
Color culoareStandard(255, 217, 106);

void setDimensiuniStandard(const VideoMode& desktop)
{
	lungimeButonStandard = desktop.width / 10;
	inaltimeButonStandard = desktop.height / 25;
	pozitieXSimbolStandard = desktop.width / 100;
	pozitieYSimbolStandard = desktop.height / 100;
}

void butonSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSalvareText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(pozitieXSimbolStandard, 5 * pozitieYSimbolStandard);
	rectangle.setFillColor(Color(255, 255, 180));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(text, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonIncarcare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(12 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Incarcare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSelectareFisier(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text, const int nr)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(12 * pozitieXSimbolStandard, (5 + 4.5 * nr) * pozitieYSimbolStandard);
	rectangle.setFillColor(Color(255, 255, 180));
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(text, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);

	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	mainText.setString(text);
	fereastraAplicatie.draw(mainText);
}

void desenareButoaneDeSelectatFisier(RenderWindow& fereastraAplicatie, const VideoMode& desktop, int pozScroll)
{
	const vector<string> fisiere = numeFisiereInFolder();
	constexpr int nrMaximDeFisiere = 7;
	const int startIdx = pozScroll;
	const int stopIdx = min(static_cast<int>(fisiere.size()), pozScroll + nrMaximDeFisiere);

	for (int i = startIdx; i < stopIdx; i++)
	{
		butonSelectareFisier(fereastraAplicatie, desktop, fisiere[i], i - startIdx);
	}
}


void butonStart(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Start", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonStop(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 9.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Stop", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonCitire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 14 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Citire", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAfisare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 18.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Afisare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAtribuire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 23 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Atribuire", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonDaca(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 27.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);

	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Decizie", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonCatTimp(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, 33 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare1);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreareSimboluri);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Cat Timp", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(78 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareRulare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Convertire C++", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonSalvareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 16;
	const int inaltimeButon = desktop.height / 24;
	RectangleShape rectangle(Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(71 * pozitieXSimbolStandard, 12 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareStandard);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineStandard);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Salvare", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonRulare(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareRulare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineRulare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Rularea codului", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonRulareTotal(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, 5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareExecutare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Rulare Total", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonRularePas(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(89 * pozitieXSimbolStandard, 9.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareExecutare);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineExecutare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Pas cu Pas", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void butonAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungimeButon = desktop.width / 40;
	const int inaltimeButon = desktop.width / 40;
	RectangleShape rectangle(Vector2f(lungimeButon, inaltimeButon));

	rectangle.setPosition(96.5 * pozitieXSimbolStandard, 94.5 * pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare2);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("?", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}
void butonDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	RectangleShape rectangle(Vector2f(lungimeButonStandard, inaltimeButonStandard));

	rectangle.setPosition(23 * pozitieXSimbolStandard, pozitieYSimbolStandard);
	rectangle.setFillColor(culoareCreare2);
	rectangle.setOutlineThickness(desktop.width / 350);
	rectangle.setOutlineColor(culoareOutlineCreare);
	fereastraAplicatie.draw(rectangle);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Instructiuni", fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(marginiText.left + marginiText.width / 2, marginiText.top + marginiText.height / 2);
	mainText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2);
	fereastraAplicatie.draw(mainText);
}

void desenareDropDown(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	butonStart(fereastraAplicatie, desktop);
	butonStop(fereastraAplicatie, desktop);
	butonCitire(fereastraAplicatie, desktop);
	butonAfisare(fereastraAplicatie, desktop);
	butonAtribuire(fereastraAplicatie, desktop);
	butonDaca(fereastraAplicatie, desktop);
}
void desenareConvertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int lungime = 60 * pozitieXSimbolStandard;
	const int inaltime = 72 * pozitieYSimbolStandard;
	RectangleShape rectangle(Vector2f(lungime, inaltime));

	rectangle.setPosition(70 * pozitieXSimbolStandard, 10 * pozitieYSimbolStandard);
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

void desenareSalvareFereastraText(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const string& text)
{
	butonSalvareText(fereastraAplicatie, desktop, text);
}

void desenareAjutor(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	float buttonX = 0.91f * pozitieXSimbolStandard;
	float buttonY = 0.83f * pozitieYSimbolStandard;
	Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);

	RenderWindow newWindow(VideoMode(static_cast<float>(50 * pozitieXSimbolStandard), static_cast<float>(50 * pozitieYSimbolStandard)), "Ajutor");
	newWindow.setFramerateLimit(60);

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText("Proiect InterSchem\n \n Blocurile se vor muta dupa mouse, daca este apasat butonul din stanga;\n \n Pentru a crea legaturi, se vor trasa cu butonul din dreapta mouse-ului; \n \n Pentru a crea blocuri, se vor apasa tastele 1(START), 2(STOP)\n 3(ATRIBUIRE), 4(CITIRE), 5(AFISARE), \n 6(DECIZIE) sau se vor folosi butoanele din meniu;\n \n Pentru a sterge un bloc si legatura sa, se va apasa ESCAPE\n \n Pentru executarea algoritmului se va folosi F12 \n \n Butonul de salvare va salva schema logica, iar cu cel de incarcare se vor \n incarca scheme logice deja facute", fontGlobal, marimeFont);
	mainText.setFillColor(Color::White);
	mainText.setPosition(pozitieXSimbolStandard, pozitieYSimbolStandard);

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