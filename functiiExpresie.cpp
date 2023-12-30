#include "functiiExpresie.h"
#include "functiiMatematice.h"
using namespace std;

void afisareTextNod(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Nod* nodCurent)
{
	static unordered_set<const Nod*> noduriVizitate;
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent))
		return;

	const int marimeFont = static_cast<int>(desktop.width) / 70;
	Text mainText(nodCurent->date.expresie, fontGlobal, marimeFont);
	noduriVizitate.insert(nodCurent);
	mainText.setFillColor(Color::Black);
	const FloatRect marginiText = mainText.getLocalBounds();
	mainText.setOrigin(static_cast<int>((marginiText.left) + marginiText.width / 2), (marginiText.top + marginiText.height) / 2);

	const int xPos = nodCurent->date.x;
	const int yPos = nodCurent->date.y;
	mainText.setPosition(xPos, yPos);
	fereastraAplicatie.draw(mainText);

	afisareTextNod(fereastraAplicatie, desktop, nodCurent->st);
	afisareTextNod(fereastraAplicatie, desktop, nodCurent->dr);
	noduriVizitate.clear();
}

void afisareTextLista(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	for (const auto a : listaArbori)
	{
		if (a.radacina == nullptr)
			continue;
		afisareTextNod(fereastraAplicatie, desktop, a.radacina);
	}
}

void stergereOutputCandMare(const int& dimensiuneMax)
{
	if (listaConsola.size() > dimensiuneMax) {
		cout << "Stergere " << listaConsola[0] << " din lista de output\n";
		listaConsola.erase(listaConsola.begin());
	}
}

void afisareListaOutput(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	if (listaConsola.empty())
		return;
	stergereOutputCandMare(10);
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	const int spatiuY = 10;
	const int spatiuMargini = 20;
	const int spatiuJos = desktop.height / 10;

	//deseneaza primul element din listaConsola (ultimul element adaugat) mai intunecat la culoare
	Text textOutput(listaConsola[listaConsola.size() - 1], fontGlobal, marimeFont);
	textOutput.setFillColor(Color::Black);
	int pozY = desktop.height - spatiuJos - textOutput.getLocalBounds().height;
	textOutput.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(textOutput);

	//deseneaza restul elementelor din listaConsola mai gri la culoare
	for (int i = listaConsola.size() - 2; i >= 0; i--) {
		Text textOutput(listaConsola[i], fontGlobal, marimeFont);
		textOutput.setFillColor(Color(90, 90, 90));
		pozY -= textOutput.getGlobalBounds().height + spatiuY;
		textOutput.setPosition(spatiuMargini, pozY);
		fereastraAplicatie.draw(textOutput);
	}
}
void functieDebugging(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	int pozY = 0;
	int spatiuY = 10;
	int spatiuMargini = 20;

	string textSimboluri = "Nr. de simboluri: " + std::to_string(numarNoduriDinListaArbori());
	Text text1(textSimboluri, fontGlobal, marimeFont);
	text1.setFillColor(Color::Black);
	text1.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(text1);
	pozY += text1.getGlobalBounds().height + spatiuY;

	string textArbori = "Nr. de elemente din fiecare arbore:";
	for (int i = 0; i < listaArbori.size(); i++)
		textArbori += " " + to_string(numarNoduriDinArbore(listaArbori[i]));
	Text text2(textArbori, fontGlobal, marimeFont);
	text2.setFillColor(Color::Black);
	text2.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(text2);
	pozY += text2.getGlobalBounds().height + spatiuY;

	string textLegaturi = ("Nr. de legaturi: " + to_string(listaLinii.size()));
	Text text3(textLegaturi, fontGlobal, marimeFont);
	text3.setFillColor(Color::Black);
	text3.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(text3);
	pozY += text3.getGlobalBounds().height + spatiuY;

	pozY = 0;
	Text text4("Resetaza lista cu 'Del'", fontGlobal, marimeFont);
	text4.setFillColor(Color::Black);
	text4.setPosition(desktop.width - spatiuMargini - text4.getLocalBounds().width, pozY);
	fereastraAplicatie.draw(text4);
	pozY += text4.getGlobalBounds().height + spatiuY;

	Text text6("Legatura cu RMB", fontGlobal, marimeFont);
	text6.setFillColor(Color::Black);
	text6.setPosition(desktop.width - spatiuMargini - text6.getLocalBounds().width, pozY);
	fereastraAplicatie.draw(text6);
	pozY += text6.getGlobalBounds().height + spatiuY;

	//(Mouse Position)
	Vector2i pozMouse = Mouse::getPosition(fereastraAplicatie);
	string textPozMouse = "(" + to_string(pozMouse.x) + "," + to_string(pozMouse.y) + ")";
	Text text5(textPozMouse, fontGlobal, marimeFont);
	text5.setFillColor(Color::Black);
	text5.setPosition(desktop.width - spatiuMargini - text5.getLocalBounds().width, pozY);
	fereastraAplicatie.draw(text5);
	pozY += text5.getGlobalBounds().height + spatiuY;

	// Text Variabile
	string textVariabile = "Variabile:";
	for (const auto& variabila : variabile) {
		textVariabile += "\n" + variabila.first + "= ";

		stringstream stream;
		stream << defaultfloat << setprecision(6) << variabila.second;
		textVariabile += stream.str();
	}

	Text textVariabileAfisate(textVariabile, fontGlobal, marimeFont);
	textVariabileAfisate.setFillColor(Color::Black);
	textVariabileAfisate.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(textVariabileAfisate);
}

void stergereSpatii(string& expresie)
{
	for (int i = 0; i < expresie.size();)
	{
		if (esteSpatiu(expresie[i]))
			expresie.erase(i, 1);
		else
			i++;
	}
}