#include "salvareDate.h"

map<const Nod*, unsigned int> noduriParcurse;
unsigned int index = 1;

void parcurgereArborePtSalvare(const Nod* nodCurent, FILE* fisier)
{
	if (noduriParcurse.find(nodCurent) != noduriParcurse.end())
		return;

	noduriParcurse[nodCurent] = index;
	fprintf(fisier, "%d,", index);
	fprintf(fisier, "%d,", nodCurent->date.tip);
	if (nodCurent->date.expresie.empty()) {
		fprintf(fisier, "#@,");
	}
	else {
		fprintf(fisier, "%s@,", nodCurent->date.expresie.c_str());
	}
	fprintf(fisier, "%f,", nodCurent->date.x);
	fprintf(fisier, "%f,", nodCurent->date.y);
	fprintf(fisier, "%f,", nodCurent->date.lungimeSimbol);
	fprintf(fisier, "%f,", nodCurent->date.inaltimeSimbol);

	if (nodCurent->st != nullptr) {
		if (noduriParcurse.find(nodCurent->st) != noduriParcurse.end())
		{
			fprintf(fisier, "%d,", noduriParcurse[nodCurent->st]);
		}
		else
		{
			fprintf(fisier, "%d,", ++index);
		}
		if (nodCurent->dr != nullptr && noduriParcurse.find(nodCurent->dr) == noduriParcurse.end()) {
			fprintf(fisier, "%d\n", index + numarNoduriMap(nodCurent->st, noduriParcurse));
		}
		else {
			fprintf(fisier, "0\n");
		}

		parcurgereArborePtSalvare(nodCurent->st, fisier);
		if (nodCurent->dr != nullptr && noduriParcurse.find(nodCurent->dr) == noduriParcurse.end()) {
			index++;
			parcurgereArborePtSalvare(nodCurent->dr, fisier);
		}
	}
	else
	{
		fprintf(fisier, "0,0\n");
	}
}

FILE* creeazaFisier(const string& numeFolder, const string& numeDefault, const string& numeExtensie) {
	const wstring wideDefault(numeDefault.begin(), numeDefault.end());
	const wstring wideExtensie(numeExtensie.begin(), numeExtensie.end());
	const wstring numeFolderTemp = wstring(numeFolder.begin(), numeFolder.end());
	const LPCWSTR folder = numeFolderTemp.c_str();
	if (!CreateDirectory(folder, nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) {
		cerr << "Nu s-a putut crea folderul: Date\n";
		return nullptr;
	}

	wstring numeFisier;
	int nr = 0;
	FILE* fisier;

	do {
		if (nr == 0) {
			numeFisier = numeFolderTemp + "/" + wideDefault + L"." + wideExtensie;
		}
		else {
			numeFisier = numeFolderTemp + "/" + wideDefault + to_wstring(nr) + L"." + wideExtensie;
		}

		fisier = _wfopen(numeFisier.c_str(), L"r");
		nr++;
	} while (fisier != nullptr);

	fisier = _wfopen(numeFisier.c_str(), L"w");
	if (fisier != nullptr) {
		wcout << L"Fisier \"" << numeFisier << L"\" creat!\n";
	}
	else {
		wcerr << L"Nu s-a putut crea fisierul " << numeFisier << L".\n";
		return nullptr;
	}
	return fisier;
}

string obtineDataCalendaristica() {
	const auto acum = chrono::system_clock::now();
	const time_t dataDeAzi = chrono::system_clock::to_time_t(acum);
	const tm* dataFormatata = localtime(&dataDeAzi);
	stringstream ss;
	ss << put_time(dataFormatata, "%d/%m/%Y");
	return ss.str();
}


void salvareDate(const VideoMode& desktop, const string& numeFisier)
{
	if (listaArbori.empty())
	{
		const string text = "Nu se poate salva o schema goala!";
		cout << text << '\n';
		listaConsola.push_back(text);
		return;
	}
	FILE* fisier = creeazaFisier("Date", numeFisier, "its");
	if (fisier == nullptr)
		return;
	const string text = "Schema a fost salvata in fisierul: \"" + numeFisier + ".its\"";
	cout << text << '\n';
	listaConsola.push_back(text);

	const string dataCalendaristica = obtineDataCalendaristica();
	fprintf(fisier, "%s\n", dataCalendaristica.c_str());
	fprintf(fisier, "Rezolutie ecran: %dx%d\n", desktop.width, desktop.height);
	fprintf(fisier, "Nr. Arbori: %d\n", static_cast<int>(listaArbori.size()));

	for (int i = 0; i < listaArbori.size(); i++)
	{
		if (listaArbori[i].radacina != nullptr) {
			fprintf(fisier, "ARBORE %d\n", i);
			fprintf(fisier, "%d\n", numarNoduri(listaArbori[i].radacina));
			noduriParcurse.clear();
			index = 1;
			parcurgereArborePtSalvare(listaArbori[i].radacina, fisier);
			fprintf(fisier, "\n");
		}
	}
	fclose(fisier);
}

void salvareCodConvertit()
{
	FILE* fisier = creeazaFisier("Cod_Convertit", "codConvertit", "cpp");
	const string codConvertit = getCodConvertit();
	fprintf(fisier, "%s", codConvertit.c_str());
	fclose(fisier);
}