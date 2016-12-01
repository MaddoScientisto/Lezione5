// Esercizio1.cpp : definisce il punto di ingresso dell'applicazione console.
//
#include "MaddoLib.h"
#include <vector>
#include <string>
using namespace std;
using namespace Maddo;
//Dichiarazione funzioni

void Game();
void InitializeCargoHold(vector<string>& inventory);
void PrintVector(vector<string> inventory, vector<string>::const_iterator iter);

// Funzioni

int main()
{
	//srand(static_cast<unsigned int>(time(0))); // Inizializzare il generatore di numeri casuali
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

	InitializeCargoHold(inventory);
	PrintVector(inventory, readOnlyIterator);

	MaddoLib::pause

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
	MaddoLib::OutputLine("your items: ");
	for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
		MaddoLib::OutputLine(*iter); // puntatore di deferenziazione, permette di accedere al contenuto della cella
	}
}