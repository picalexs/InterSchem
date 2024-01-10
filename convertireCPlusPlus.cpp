#include "convertireCPlusPlus.h"
using namespace std;

string codConvertit;
int nrStart = 0, nrStop = 0;
int nrAcolade = 0;

string getCodConvertit()
{
	return codConvertit;
}

void convertireInCodRec(const Nod* nodCurent, const RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	static set<const Nod*> noduriVizitate;
	if (nodCurent == nullptr || noduriVizitate.count(nodCurent) != 0)
		return;
	noduriVizitate.insert(nodCurent);
	if (nodCurent->date.tip == TipNod::START)
	{
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::STOP)
		return;
	if (nodCurent->date.tip == TipNod::ATRIBUIRE)
	{
		codConvertit += "float " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::CITIRE)
	{
		codConvertit += "cin>> " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::AFISARE)
	{
		codConvertit += "cout<< " + nodCurent->date.expresie + ";\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
	}
	if (nodCurent->date.tip == TipNod::DACA)
	{
		codConvertit += "if(" + nodCurent->date.expresie + ")" + "\n";
		codConvertit += "{\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		codConvertit += "}\n";
		codConvertit += "else\n";
		codConvertit += "{\n";
		convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
		codConvertit += "}\n";
	}
	if (nodCurent->date.tip == TipNod::CAT_TIMP)
	{
		codConvertit += "while(" + nodCurent->date.expresie + ")" + "\n";
		codConvertit += "{\n";
		convertireInCodRec(nodCurent->st, fereastraAplicatie, desktop);
		codConvertit += "}\n";
		convertireInCodRec(nodCurent->dr, fereastraAplicatie, desktop);
	}
	noduriVizitate.clear();
}

void convertire(RenderWindow& fereastraAplicatie, const VideoMode& desktop)
{
	codConvertit.clear();
	if (!esteAlgoritmCorect())
		return;
	codConvertit += "#include <iostream>\n";
	codConvertit += "#include <cmath>\n";
	codConvertit += "using namespace std;\n";
	codConvertit += "#int main()\n";
	codConvertit += "{\n";

	convertireInCodRec(listaArbori[0].radacina, fereastraAplicatie, desktop);

	codConvertit += "return 0;\n";
	codConvertit += "}\n";

	cout << "Codul a fost convertit!\n";

	const int marimeFont = static_cast<int>(desktop.width) / 90;
	Text mainText(codConvertit, fontGlobal, marimeFont);
	mainText.setFillColor(Color::Black);
	mainText.setPosition(71 * desktop.width / 100, 20 * desktop.height / 100);
	fereastraAplicatie.draw(mainText);
}
