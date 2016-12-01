// Esercizio1.cpp : definisce il punto di ingresso dell'applicazione console.
//
#include "MaddoLib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;
using namespace Maddo;
//Dichiarazione funzioni

void Game();
void InitializeCargoHold(vector<string>& inventory);
void PrintVector(vector<string> inventory, vector<string>::const_iterator iter);

// Funzioni

int main()
{
	srand(static_cast<unsigned int>(time(0))); // Inizializzare il generatore di numeri casuali
	bool exit = false;
	while (!exit) {
		Game();

		exit = MaddoLib::AskYesNo("\nUscire dal programma?");
	}
	return 0;
}

void Game()
{
	vector<string> inventory;

	vector<string>::iterator iterator; 
	vector<string>::const_iterator readOnlyIterator;
	string str;

	InitializeCargoHold(inventory);
	PrintVector(inventory, readOnlyIterator);

	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	 str = inventory.back(); // back e non end
	inventory.pop_back();

	MaddoLib::OutputLine(str + " non era legato bene ed è caduto in acqua");
	PrintVector(inventory, readOnlyIterator);
	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	inventory.push_back("tè");
	MaddoLib::OutputLine("Un mercante ti dona del tè");
	PrintVector(inventory, readOnlyIterator);

	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	MaddoLib::OutputLine("Arrivi ad un mercato e scambi lana con frumento");

	iterator = find(inventory.begin(), inventory.end(), "lana");
	*iterator = "frumento";

	PrintVector(inventory, readOnlyIterator);

	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	MaddoLib::OutputLine("Dei pirati ti attaccano e ti rubano il vino");
	iterator = find(inventory.begin(), inventory.end(), "vino");
	inventory.erase(iterator);

	PrintVector(inventory, readOnlyIterator);
	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	MaddoLib::OutputLine("Ordini l'inventario in ordine alfabetico");
	sort(inventory.begin(), inventory.end());
	PrintVector(inventory, readOnlyIterator);
	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	random_shuffle(inventory.begin(), inventory.end());
	MaddoLib::OutputLine("Una tempesta mescola tutto il carico");
	PrintVector(inventory, readOnlyIterator);
	MaddoLib::Pause();
	MaddoLib::ClearScreen();

	MaddoLib::OutputLine("Infine giungi al mercato e vendi tutto il tuo carico");

	for (auto & element : inventory) {
		element = "oro";
	}

	PrintVector(inventory, readOnlyIterator);
	MaddoLib::Pause();
	MaddoLib::ClearScreen();
}

void InitializeCargoHold(vector<string>& inventory)
{
	inventory.clear();
	inventory.push_back("vino");
	inventory.push_back("lana");
	inventory.push_back("avorio");
	inventory.push_back("legno");

}

void PrintVector(vector<string> inventory, vector<string>::const_iterator iter) 
{
	MaddoLib::OutputLine("Carico corrente della nave: ");
	for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
		MaddoLib::OutputLine(*iter);
	}
}

