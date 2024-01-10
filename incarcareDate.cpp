#include "incarcareDate.h"
#include "logicaInput.h"

void conversieDateEcran(float& x, float& y, const VideoMode& desktop, const int& lngEcran, const int& latEcran)
{
	//converteste datele din fisier in date pentru ecran
	x = x * desktop.width / lngEcran;
	y = y * desktop.height / latEcran;
}

void creareNod(const VideoMode& desktop, FILE* fisier, char buffer[256], vector<Nod*>& noduri, vector<pair<unsigned int, unsigned int>>& legaturi, const int& lngEcran, const int& latEcran)
{
	fgets(buffer, 256, fisier);
	const int index = atoi(strtok(buffer, ","));
	const int tip = atoi(strtok(nullptr, ","));
	string expresie = strtok(nullptr, "@");
	if (expresie == "#")
	{
		expresie.clear();
	}
	float x = atof(strtok(nullptr, ","));
	float y = atof(strtok(nullptr, ","));
	conversieDateEcran(x, y, desktop, lngEcran, latEcran);
	float lungimeSimbol = atof(strtok(nullptr, ","));
	float inaltimeSimbol = atof(strtok(nullptr, ","));
	conversieDateEcran(lungimeSimbol, inaltimeSimbol, desktop, lngEcran, latEcran);

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

	Arbore ArboreNou;
	atribuireArbore(ArboreNou, nod->date);
	listaArbori.push_back(ArboreNou);
	adaugaSimbolCaObstacole(ArboreNou.radacina);

	legaturi[index - 1].first = indexSt;
	legaturi[index - 1].second = indexDr;
}

void creareListaArbori(FILE* fisier, const VideoMode& desktop)
{
	char buffer[256];
	fgets(buffer, 256, fisier); // Citeste data

	int lngEcran = 0, latEcran = 0;
	fgets(buffer, 256, fisier); // Citeste linia ce contine dimensiunile ecranului
	strtok(buffer, ":");
	lngEcran = atoi(strtok(nullptr, "x"));
	latEcran = atoi(strtok(nullptr, "x"));

	fgets(buffer, 256, fisier);
	strtok(buffer, ":"); // Citeste linia ce contine numarul de arbori
	const int nrArbori = atoi(strtok(nullptr, ":"));

	for (int arboreIndex = 0; arboreIndex < nrArbori; arboreIndex++) {
		fgets(buffer, 256, fisier); // Citeste linia ARBORE NR
		fgets(buffer, 256, fisier); // Citeste linia ce contine numarul de noduri
		const int nrNoduri = atoi(buffer);
		vector<Nod*> noduri(nrNoduri);
		vector<pair<unsigned int, unsigned int>> legaturi(nrNoduri);

		for (int i = 0; i < nrNoduri; i++) {
			creareNod(desktop, fisier, buffer, noduri, legaturi, lngEcran, latEcran);//Citeste cat un nod
		}
		fgets(buffer, 256, fisier); // Citeste linia goala

		for (int idx = 0; idx < legaturi.size(); idx++)
		{
			Nod* nod1 = nullptr;
			if (legaturi[idx].first != 0 || legaturi[idx].second != 0) {
				nod1 = gasesteNodInListaArbori(noduri[idx]->date);
			}

			if (legaturi[idx].first != 0)
			{
				Nod* nod2 = gasesteNodInListaArbori(noduri[legaturi[idx].first - 1]->date);
				adaugaLinie(nod1, nod2);
			}
			if (legaturi[idx].second != 0)
			{
				Nod* nod2 = gasesteNodInListaArbori(noduri[legaturi[idx].second - 1]->date);
				adaugaLinie(nod1, nod2);
			}
		}
	}
}

void incarcareDate(const VideoMode& desktop)
{
	const string numeFisier = "date.its";//temporar
	FILE* fisier = fopen(numeFisier.c_str(), "r");
	if (fisier == nullptr)
	{
		cout << "Fisierul nu a putut fi deschis.\n";
		return;
	}

	logicaDelete();
	creareListaArbori(fisier, desktop);

	fclose(fisier);
	fisier = nullptr;
}