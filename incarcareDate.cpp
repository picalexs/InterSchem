#include "incarcareDate.h"

void creareNod(FILE* fisier, char buffer[256], vector<Nod*>& noduri)
{
	fgets(buffer, 256, fisier);
	const int index = atoi(strtok(buffer, ","));
	const int tip = atoi(strtok(nullptr, ","));
	string expresie = strtok(nullptr, ",");
	if (expresie == "#")
	{
		expresie.clear();
	}
	const float x = atof(strtok(nullptr, ","));
	const float y = atof(strtok(nullptr, ","));
	const float lungimeSimbol = atof(strtok(nullptr, ","));
	const float inaltimeSimbol = atof(strtok(nullptr, ","));
	const int indexSt = atoi(strtok(nullptr, ","));
	const int indexDr = atoi(strtok(nullptr, ","));
	Nod* nod = new Nod;

	nod->date.tip = static_cast<TipNod>(tip);
	nod->date.expresie = expresie;
	nod->date.x = x;
	nod->date.y = y;
	nod->date.lungimeSimbol = lungimeSimbol;
	nod->date.inaltimeSimbol = inaltimeSimbol;
	noduri[index - 1] = nod;
}

void creareListaArbori(FILE* fisier)
{
	char buffer[256];
	fgets(buffer, 256, fisier);
	const int nrArbori = atoi(buffer);
	listaArbori.resize(nrArbori);


	for (int arboreIndex = 0; arboreIndex < nrArbori; arboreIndex++) {
		fgets(buffer, 256, fisier); // Citeste linia ARBORE NR
		fgets(buffer, 256, fisier); // Citeste linia ce contine numarul de noduri
		const int nrNoduri = atoi(buffer);
		vector<Nod*> noduri(nrNoduri);

		for (int i = 0; i < nrNoduri; i++) {
			creareNod(fisier, buffer, noduri);//Citeste cat un nod
		}

		for (int i = 0; i < noduri.size(); i++)
		{

		}
	}
}

void incarcareDate()
{
	const string numeFisier = "date.its";//temporar
	FILE* fisier = fopen(numeFisier.c_str(), "r");
	if (fisier == nullptr)
	{
		cout << "Fisierul nu a putut fi deschis.\n";
		return;
	}

	creareListaArbori(fisier);

	fclose(fisier);
	fisier = nullptr;
}