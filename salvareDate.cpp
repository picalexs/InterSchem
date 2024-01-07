#include "salvareDate.h"
#include <cstdio>
#include <set>

unsigned int index = 1;
void parcurgereArborePtSalvare(const Nod* nodCurent, FILE* fisier)
{
	static set<Nod*> noduriParcurse;
	if (noduriParcurse.count(const_cast<Nod*>(nodCurent)) != 0)
		return;
	noduriParcurse.insert(const_cast<Nod*>(nodCurent));
	fprintf(fisier, "%d,", index);
	fprintf(fisier, "%d,", nodCurent->date.tip);
	fprintf(fisier, "%s,", nodCurent->date.expresie.c_str());
	fprintf(fisier, "%f,", nodCurent->date.x);
	fprintf(fisier, "%f,", nodCurent->date.y);
	fprintf(fisier, "%f,", nodCurent->date.lungimeSimbol);
	fprintf(fisier, "%f,", nodCurent->date.inaltimeSimbol);

	if (nodCurent->st != nullptr) {
		fprintf(fisier, "%d,", ++index);
		if (nodCurent->dr != nullptr) {
			fprintf(fisier, "%d\n", index + numarNoduri(nodCurent->st));
		}
		else {
			fprintf(fisier, "0\n");
		}
		parcurgereArborePtSalvare(nodCurent->st, fisier);
		if (nodCurent->dr != nullptr) {
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

	for (int i = 0; i < listaArbori.size(); i++)
	{
		if (listaArbori[i].radacina != nullptr) {
			fprintf(fisier, "ARBORE %d\n", i);
			parcurgereArborePtSalvare(listaArbori[i].radacina, fisier);
			index = 1;
			fprintf(fisier, "\n");
		}
	}
	fclose(fisier);
}