#include "logicaButoane.h"

using namespace sf;

bool verificareButon(const Vector2i& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime && pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

void logicaButoaneCreareSimboluri(const RenderWindow& fereastraAplicatie, const Vector2i pozitieMouse, const VideoMode& desktop, const bool& esteActivatDrop)
{
	if (!esteActivatDrop)
		return;
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton start
		logicaCreareSimbol(fereastraAplicatie, desktop, 0);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 9.5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton stop
		logicaCreareSimbol(fereastraAplicatie, desktop, 1);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 14 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton citire
		logicaCreareSimbol(fereastraAplicatie, desktop, 3);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 18.5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton afisare
		logicaCreareSimbol(fereastraAplicatie, desktop, 4);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 23 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton atribuire
		logicaCreareSimbol(fereastraAplicatie, desktop, 2);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 27.5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton decizie
		logicaCreareSimbol(fereastraAplicatie, desktop, 5);
	}
}

void logicaButoaneRulare(const Vector2i pozitieMouse, VideoMode desktop, const bool& esteActivatDropRulare)
{
	if (!esteActivatDropRulare)
		return;
	if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		cout << "Apasat Buton Rulare Totala!\n";
	}
	else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 9.5 * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		executareAlgoritmPasCuPas();
		cout << "Apasat Buton Rulare Pas cu Pas!\n";
	}

}

void logicaFisiere(const Vector2i pozitieMouse, VideoMode desktop, bool& esteApasatSalvare, bool& esteApasatIncarcare)
{
	if (verificareButon(pozitieMouse, desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		esteApasatSalvare = !esteApasatSalvare;
		activeazaSalvare();
		cout << "Apasat Buton Salvare!\n";
	}
	else if (verificareButon(pozitieMouse, 12 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		esteApasatIncarcare = !esteApasatIncarcare;
		cout << "Apasat Buton Incarcare!\n";
	}
	if (verificareButon(pozitieMouse, 71 * desktop.width / 100, 12 * desktop.height / 100, desktop.width / 16, desktop.height / 24)) {
		salvareCodConvertit();
		cout << "Apasat Buton Salvare Convertire!\n";
	}
}

void logicaMeniuri(RenderWindow& fereastraAplicatie, const Vector2i& pozitieMouse, const VideoMode& desktop, bool& esteActivatDrop, bool& esteActivatDropRulare, bool& esteActivatConvertire)
{
	if (esteActivatDrop || verificareButon(pozitieMouse, 23 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//meniu creare simboluri
		esteActivatDrop = !esteActivatDrop;
	}
	else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//meniu rulare
		esteActivatDropRulare = !esteActivatDropRulare;
	}
	else if (verificareButon(pozitieMouse, 96.6 * desktop.width / 100, 94.5 * desktop.height / 100, desktop.width / 40, desktop.width / 40))
	{//buton ajutor
		desenareAjutor(fereastraAplicatie, desktop);
	}
	else if (verificareButon(pozitieMouse, 78 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//buton convertire
		esteActivatConvertire = !esteActivatConvertire;
	}
}

void logicaApasareButonIncarcare(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, int pozScroll, bool& esteApasatIncarcare)
{//verifica daca s-a apasat pe unul din butoanele de incarcare ce contin numele fisierelor salvate
	if (!esteApasatIncarcare)
		return;
	const vector<string> fisiere = numeFisiereInFolder();
	constexpr int nrMaximDeFisiere = 7;
	const int startIdx = pozScroll;
	const int stopIdx = min(static_cast<int>(fisiere.size()), pozScroll + nrMaximDeFisiere);

	for (int i = startIdx; i < stopIdx; i++)
	{
		if (verificareButon(Mouse::getPosition(fereastraAplicatie), 12 * desktop.width / 100, (5 + 4 * (i - startIdx)) * desktop.height / 100, desktop.width / 10, desktop.height / 25))
		{
			incarcareDate(desktop, fisiere[i]);
			esteApasatIncarcare = false;
			break;
		}
	}
}

void logicaScroll(const Event& event, bool& aFostFolositScroll, int& pozScroll)
{//face scroll la continutul paginii de butoane de incarcare
	if (event.type == Event::MouseWheelScrolled)
	{
		if (!aFostFolositScroll) {
			if (event.mouseWheelScroll.delta > 0)
				pozScroll = max(0, pozScroll - 2); // Scroll sus
			else if (event.mouseWheelScroll.delta < 0)
				pozScroll = min(0, min(static_cast<int>(numeFisiereInFolder().size()) - 7, pozScroll + 2)); // Scroll jos
			aFostFolositScroll = true;
		}
	}
	else if (aFostFolositScroll)
	{
		aFostFolositScroll = false;
	}
}

void logicaButon(RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Event& event)
{
	static bool esteApasatMouse = false;
	static bool esteActivatDrop = false;
	static bool esteActivatDropRulare = false;
	static bool esteActivatConvertire = false;
	static bool esteApasatSalvare = false;
	static bool esteApasatIncarcare = false;
	static int pozScroll = 0;
	static bool aFostFolositScroll = false;

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && esteApasatMouse == false)
	{
		esteApasatMouse = true;
	}
	if (!(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) && esteApasatMouse == true)
	{
		const Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);

		logicaButoaneCreareSimboluri(fereastraAplicatie, pozitieMouse, desktop, esteActivatDrop);
		logicaButoaneRulare(pozitieMouse, desktop, esteActivatDropRulare);
		logicaFisiere(pozitieMouse, desktop, esteApasatSalvare, esteApasatIncarcare);
		logicaMeniuri(fereastraAplicatie, pozitieMouse, desktop, esteActivatDrop, esteActivatDropRulare, esteActivatConvertire);
		logicaApasareButonIncarcare(fereastraAplicatie, desktop, pozScroll, esteApasatIncarcare);

		esteApasatMouse = false;
	}
	logicaScroll(event, aFostFolositScroll, pozScroll);

	static string numeFisierDeSalvat;

	if (esteApasatSalvare)
	{
		if (!seCitesteSalvare())
		{
			//s-a oprit citirea si se salveaza
			if (!numeFisierDeSalvat.empty() && numeFisierDeSalvat.back() == '\r')
				numeFisierDeSalvat.pop_back();
			salvareDate(desktop, numeFisierDeSalvat);
			numeFisierDeSalvat.clear();
			esteApasatSalvare = false;
		}
		else {
			//citeste numele fisierului de salvat
			const string numeTmp = getNumeFisierSalvare();
			if (!numeTmp.empty())
				numeFisierDeSalvat = numeTmp;
			if (!numeFisierDeSalvat.empty() && numeFisierDeSalvat.back() == '\r')
				numeFisierDeSalvat.pop_back();
			desenareSalvareFereastraText(fereastraAplicatie, desktop, numeFisierDeSalvat);
		}
	}

	if (esteApasatIncarcare)
	{//deseneaza meniul de incarcare
		desenareButoaneDeSelectatFisier(fereastraAplicatie, desktop, pozScroll);
	}
	if (esteActivatDrop) {
		//deseneaza meniul de creare simboluri
		desenareDropDown(fereastraAplicatie, desktop);
	}
	if (esteActivatConvertire) {
		//deseneaza meniul de convertire
		desenareConvertire(fereastraAplicatie, desktop);
		convertire(fereastraAplicatie, desktop);
	}
	if (esteActivatDropRulare) {
		//deseneaza meniul de rulare
		desenareDropDownRulare(fereastraAplicatie, desktop);
	}
}
