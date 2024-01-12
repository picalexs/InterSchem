#include "functiiExpresie.h"
#include "functiiMatematice.h"
using namespace std;

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
	constexpr float spatiuY = 10;
	constexpr float spatiuMargini = 20;
	const float spatiuJos = static_cast<float>(desktop.height) / 50;

	//deseneaza primul element din listaConsola (ultimul element adaugat) mai intunecat la culoare
	Text textOutput(listaConsola[listaConsola.size() - 1], fontGlobal, marimeFont);
	textOutput.setFillColor(Color::Black);
	float pozY = desktop.height - spatiuJos - textOutput.getLocalBounds().height;
	textOutput.setPosition(spatiuMargini, pozY);
	fereastraAplicatie.draw(textOutput);

	//deseneaza restul elementelor din listaConsola mai gri la culoare
	for (size_t i = listaConsola.size() - 1; i > 0; --i) {
		Text textOutput(listaConsola[i - 1], fontGlobal, marimeFont);
		textOutput.setFillColor(Color(90, 90, 90));
		pozY -= textOutput.getGlobalBounds().height + spatiuY;
		textOutput.setPosition(spatiuMargini, pozY);
		fereastraAplicatie.draw(textOutput);
	}
}

void afisareVariabile(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	constexpr float spatiuMargini = 20;

	string textVariabile = "Variabile:";
	for (const auto& variabila : variabile) {
		if ((variabila.first == "PI" && variabila.second == obtineValDupaNume("PI"))
			|| (variabila.first == "e" && variabila.second == obtineValDupaNume("e"))
			|| (variabila.first == "g" && variabila.second == obtineValDupaNume("g"))
			|| (variabila.first == "phi" && variabila.second == obtineValDupaNume("phi")))
			continue;

		textVariabile += "\n" + variabila.first + "= ";
		stringstream stream;
		stream << defaultfloat << setprecision(6) << variabila.second;
		textVariabile += stream.str();
	}
	if (textVariabile == "Variabile:")
		return;

	Text textVariabileAfisate(textVariabile, fontGlobal, marimeFont);
	textVariabileAfisate.setFillColor(Color::Black);
	textVariabileAfisate.setPosition(spatiuMargini, desktop.height / 10);
	fereastraAplicatie.draw(textVariabileAfisate);
}

void functieDebugging(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	const int marimeFont = static_cast<int>(desktop.width) / 70;
	float pozY = desktop.height / 15;
	float spatiuY = 10;
	float spatiuMargini = 20;

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