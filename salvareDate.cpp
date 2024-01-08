#include "salvareDate.h"
#include <cstdio>
#include <set>

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
		fprintf(fisier, "#,");
	}
	else {
		fprintf(fisier, "%s,", nodCurent->date.expresie.c_str());
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

FILE* creeazaFisier(const string& numeDefault) {
	string numeFisier;
	int nr = 0;
	FILE* fisier;

	do {
		if (nr == 0) {
			numeFisier = numeDefault + ".its";
		}
		else {
			numeFisier = numeDefault + to_string(nr) + ".its";
		}
		fisier = fopen(numeFisier.c_str(), "r");
		nr++;
	} while (fisier != nullptr);

	fisier = fopen(numeFisier.c_str(), "w");
	if (fisier != nullptr) {
		cout << "Fisier \"" << numeFisier << "\" creat!\n";
	}
	else {
		cout << "Nu s-a putut crea fisierul " << numeFisier << ".\n";
	}
	return fisier;
}

void salvareDate()
{
	FILE* fisier = creeazaFisier("date");

	fprintf(fisier, "%d\n", listaArbori.size());
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