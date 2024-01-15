#include "logicaButoane.h"

#include "convertireCPlusPlus.h"

using namespace sf;

bool verificareButon(const Vector2f& pozitieMouse, float x, float y, float lungime, float inaltime) {
	return (pozitieMouse.x >= x && pozitieMouse.x <= x + lungime && pozitieMouse.y >= y && pozitieMouse.y <= y + inaltime);
}

void logicaButoaneCreareSimboluri(const RenderWindow& fereastraAplicatie, const Vector2f pozitieMouse, const VideoMode& desktop, const bool& esteActivatDrop)
{
	if (!esteActivatDrop)
		return;
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 5.5f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton start
		logicaCreareSimbol(fereastraAplicatie, desktop, 0);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 10.0f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton stop
		logicaCreareSimbol(fereastraAplicatie, desktop, 1);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 14.5f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton citire
		logicaCreareSimbol(fereastraAplicatie, desktop, 3);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 19.0f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton afisare
		logicaCreareSimbol(fereastraAplicatie, desktop, 4);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 23.5f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton atribuire
		logicaCreareSimbol(fereastraAplicatie, desktop, 2);
	}
	if (verificareButon(pozitieMouse, 23 * desktop.width / 100, 28.0f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		///buton decizie
		logicaCreareSimbol(fereastraAplicatie, desktop, 5);
	}
}

void logicaButoaneRulare(const Vector2f& pozitieMouse, VideoMode desktop, const bool& esteActivatDropRulare)
{
	if (!esteActivatDropRulare)
		return;
	if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 10.0f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		cout << "Apasat Buton Rulare Totala!\n";
		activeazaParcurgereaTotala();
	}
	else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, 5.5f * desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		if (!seCitesteParcurgereProgram())
			executareAlgoritmPasCuPas();
		cout << "Apasat Buton Rulare Pas cu Pas!\n";
	}

}

void logicaFisiere(const Vector2f& pozitieMouse, const VideoMode& desktop, bool& esteApasatSalvare, bool& esteApasatIncarcare)
{
	if (verificareButon(pozitieMouse, desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		esteApasatSalvare = !esteApasatSalvare;
		if (esteApasatSalvare)
			activeazaSalvare();
		else
			opresteSalvare();
		cout << "Apasat Buton Salvare!\n";
	}
	else if (verificareButon(pozitieMouse, 12 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25)) {
		esteApasatIncarcare = !esteApasatIncarcare;
		cout << "Apasat Buton Incarcare!\n";
	}
	if (verificareButon(pozitieMouse, 71 * desktop.width / 100, 8 * desktop.height / 100, desktop.width / 16, desktop.height / 24)) {
		salvareCodConvertit();
		cout << "Apasat Buton Salvare Convertire!\n";
	}
}

void logicaMeniuri(RenderWindow& fereastraAplicatie, const Vector2f& pozitieMouse, const VideoMode& desktop, bool& esteActivatDrop, bool& esteActivatDropRulare, bool& esteActivatConvertire, bool& esteConvertitCodul)
{
	if (esteActivatDrop || verificareButon(pozitieMouse, 23 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//meniu creare simboluri
		esteActivatDrop = !esteActivatDrop;
	}
	else if (verificareButon(pozitieMouse, 89 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//meniu rulare
		esteActivatDropRulare = !esteActivatDropRulare;
		if (esteActivatDropRulare && esteActivatConvertire)
			esteActivatConvertire = false;
	}
	else if (verificareButon(pozitieMouse, 96.5f * desktop.width / 100, 94.5f * desktop.height / 100, desktop.width / 40, desktop.width / 40))
	{//buton ajutor
		cout << "Apasat Buton Ajutor!\n";
		desenareAjutor(fereastraAplicatie, desktop);
	}
	else if (verificareButon(pozitieMouse, 78 * desktop.width / 100, desktop.height / 100, desktop.width / 10, desktop.height / 25))
	{//buton convertire
		esteActivatConvertire = !esteActivatConvertire;
		if (esteActivatConvertire && esteActivatDropRulare)
			esteActivatDropRulare = false;
		esteConvertitCodul = false;
	}
}

void logicaApasareButonIncarcare(const RenderWindow& fereastraAplicatie, const VideoMode& desktop, const Vector2f& pozitieMouse, const int& pozScroll, bool& esteApasatIncarcare)
{//verifica daca s-a apasat pe unul din butoanele de incarcare ce contin numele fisierelor salvate
	if (!esteApasatIncarcare)
		return;
	vector<string> fisiere = numeFisiereInFolder();
	constexpr int nrMaximDeFisiere = 7;
	const int startIdx = pozScroll;
	const int stopIdx = min(static_cast<int>(fisiere.size()), pozScroll + nrMaximDeFisiere);
	for (int i = startIdx; i < stopIdx; i++)
	{
		if (verificareButon(pozitieMouse, 12 * desktop.width / 100, (5 + 4 * (i - startIdx)) * desktop.height / 100, desktop.width / 10, desktop.height / 25))
		{
			incarcareDateFisier(desktop, fisiere[i]);
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
				pozScroll = max(0, min(static_cast<int>(numeFisiereInFolder().size()) - 7, pozScroll + 2)); // Scroll jos
			aFostFolositScroll = true;
		}
	}
	else if (aFostFolositScroll)
	{
		aFostFolositScroll = false;
	}
}

void logicaSalvare(RenderWindow& fereastraAplicatie, const VideoMode& desktop, bool& esteApasatSalvare, string& numeFisierDeSalvat)
{
	if (!esteApasatSalvare)
		return;
	if (!seCitesteSalvare())
	{
		//s-a oprit citirea si se salveaza
		if (!numeFisierDeSalvat.empty() && numeFisierDeSalvat.back() == '\r')
			numeFisierDeSalvat.pop_back();
		salvareDateFisier(desktop, numeFisierDeSalvat);
		numeFisierDeSalvat.clear();
		esteApasatSalvare = false;
	}
	else {
		//citeste numele fisierului de salvat
		const string numeTmp = getNumeFisierSalvare();
		if (numeTmp.empty()) {
			desenareSalvareFereastraText(fereastraAplicatie, desktop, numeTmp);
			return;
		}
		numeFisierDeSalvat = numeTmp;
		if (!numeFisierDeSalvat.empty() && numeFisierDeSalvat.back() == '\r')
			numeFisierDeSalvat.pop_back();
		desenareSalvareFereastraText(fereastraAplicatie, desktop, numeFisierDeSalvat);
	}

}

int marimeFont = 0;

void updateMarimeFont(const int marime)
{
	marimeFont = marime;
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
	static bool esteConverititCodul = false;


	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && esteApasatMouse == false)
	{
		esteApasatMouse = true;
	}
	if (!(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) && esteApasatMouse == true)
	{
		const Vector2i pozitieMouse = Mouse::getPosition(fereastraAplicatie);
		const Vector2f pozitieMouseWorld = fereastraAplicatie.mapPixelToCoords(pozitieMouse);

		logicaButoaneCreareSimboluri(fereastraAplicatie, pozitieMouseWorld, desktop, esteActivatDrop);
		logicaButoaneRulare(pozitieMouseWorld, desktop, esteActivatDropRulare);
		logicaFisiere(pozitieMouseWorld, desktop, esteApasatSalvare, esteApasatIncarcare);
		logicaMeniuri(fereastraAplicatie, pozitieMouseWorld, desktop, esteActivatDrop, esteActivatDropRulare, esteActivatConvertire, esteConverititCodul);
		logicaApasareButonIncarcare(fereastraAplicatie, desktop, pozitieMouseWorld, pozScroll, esteApasatIncarcare);

		esteApasatMouse = false;
	}
	static string numeFisierDeSalvat;
	logicaScroll(event, aFostFolositScroll, pozScroll);
	logicaSalvare(fereastraAplicatie, desktop, esteApasatSalvare, numeFisierDeSalvat);

	if (esteApasatIncarcare)
	{//deseneaza meniul de incarcare
		desenareButoaneDeSelectatFisier(fereastraAplicatie, pozScroll);
	}
	if (esteActivatDrop) {
		//deseneaza meniul de creare simboluri
		desenareDropDown(fereastraAplicatie);
	}
	if (esteActivatDropRulare) {
		//deseneaza meniul de rulare
		desenareDropDownRulare(fereastraAplicatie, desktop);
	}
	if (esteActivatConvertire) {
		//deseneaza meniul de convertire
		if (!esteConverititCodul) {
			convertire(fereastraAplicatie, desktop);
			esteConverititCodul = true;
		}
		desenareConvertire(fereastraAplicatie, desktop, marimeFont);
	}
}
