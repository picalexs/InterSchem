#include "functiiExpresie.h"
#include <iomanip>
#include <sstream>
using namespace std;

void afisareTextNod(RenderWindow& window, VideoMode& desktop, const nod* nodCurent)
{
	static unordered_set<const nod*> noduriVizitate;
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent))
		return;

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(nodCurent->date.expresie, fontGlobal, marimeFont);
	noduriVizitate.insert(nodCurent);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(static_cast<int>((marginiText.left) + marginiText.width / 2), 10);

	const int xPos = nodCurent->date.x;
	const int yPos = nodCurent->date.y + 25;
	mainText.setPosition(xPos, yPos);
	window.draw(mainText);

	afisareTextNod(window,desktop, nodCurent->st);
	afisareTextNod(window,desktop, nodCurent->dr);
	noduriVizitate.clear();
}

void afisareTextLista(RenderWindow& window, VideoMode& desktop)
{
	for (const auto a : listaArbori)
	{
		if (a.radacina == nullptr)
			continue;
		afisareTextNod(window,desktop, a.radacina);
	}
}


void afisareListaOutput(RenderWindow& window, const VideoMode& desktop)
{
	if (listaConsola.empty())
		return;
	const int marimeFont = desktop.width / 70;
	//deseneaza primul element din listaConsola (ultimul element adaugat) mai intunecat la culoare
	Text textOutput(listaConsola[listaConsola.size() - 1], fontGlobal, marimeFont);
	textOutput.setFillColor(Color::Black);
	textOutput.setPosition(10, 765);
	window.draw(textOutput);

	//deseneaza restul elementelor din listaConsola mai gri la culoare
	size_t index = 1;
	for (size_t i = listaConsola.size() - 2; i >= 0; i--) {
		Text textOutput(listaConsola[i], fontGlobal, marimeFont);
		textOutput.setFillColor(Color(90, 90, 90));
		textOutput.setPosition(10, 765 - index * 15);
		window.draw(textOutput);
		index++;
	}
}

void functieDebugging(RenderWindow& window, VideoMode& desktop)
{
	int marimeFont = desktop.width / 70;
	string textSimboluri = "Nr. de simboluri: " + std::to_string(numarNoduriDinListaArbori());
	Text text1(textSimboluri, fontGlobal, marimeFont);
	text1.setFillColor(Color::Black);
	text1.setPosition(10, 0);
	window.draw(text1);

	string textArbori = "Nr. de elemente din fiecare arbore:";
	for (int i = 0; i < listaArbori.size(); i++)
		textArbori += " " + to_string(numarNoduriDinArbore(listaArbori[i]));
	Text text2(textArbori, fontGlobal, marimeFont);
	text2.setFillColor(Color::Black);
	text2.setPosition(10, 15);
	window.draw(text2);

	string textLegaturi = ("Nr. de legaturi: " + to_string(listaLinii.size()));
	Text text3(textLegaturi, fontGlobal, marimeFont);
	text3.setFillColor(Color::Black);
	text3.setPosition(10, 30);
	window.draw(text3);

	Text text4("Resetaza lista cu 'Del'.", fontGlobal, marimeFont);
	text4.setFillColor(Color::Black);
	text4.setPosition(840, 0);
	window.draw(text4);

	Text text6("Legatura cu RMB", fontGlobal, marimeFont);
	text6.setFillColor(Color::Black);
	text6.setPosition(870, 15);
	window.draw(text6);

	//deseneaza pozitia de la mouse pe ecran
	Vector2i pozMouse = Mouse::getPosition(window);
	string textPozMouse = "(" + to_string(pozMouse.x) + "," + to_string(pozMouse.y) + ")";
	Text text5(textPozMouse, fontGlobal, marimeFont);
	text5.setFillColor(Color::Black);
	text5.setPosition(925, 30);
	window.draw(text5);

	//deseneaza variabilele folosite pe ecran
	string textVariabile = "Variabile:";
	for (const auto& variabila : variabile) {
		textVariabile += "\n" + variabila.first + "= ";

		stringstream stream;
		stream << defaultfloat << setprecision(6) << variabila.second;
		textVariabile += stream.str();
	}

	Text textVariabileAfisate(textVariabile, fontGlobal, marimeFont);
	textVariabileAfisate.setFillColor(Color::Black);
	textVariabileAfisate.setPosition(10, 55);
	window.draw(textVariabileAfisate);
}