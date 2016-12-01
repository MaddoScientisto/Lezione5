// 2016-11-24.cpp : definisce il punto di ingresso dell'applicazione console.


#include "MaddoLib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace Maddo;

void Inventory();
void PrintInventory(vector<string> inventory, vector<string>::const_iterator iter);
void HighScores();
void hangaman();

int main()
{
	MaddoLib::OutputLine("Ayy lmao");
	//Inventory();
	hangaman();
	return 0;
}

void PrintInventory(vector<string> inventory, vector<string>::const_iterator iter) {
	MaddoLib::Output("your items: ");
	for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
		MaddoLib::OutputLine(*iter); // puntatore di deferenziazione, permette di accedere al contenuto della cella
	}
}

void Inventory() {
	//vector<string>::iterator myIterator;

	vector<string> inventory;
	inventory.push_back("sword");
	inventory.push_back("armor");
	inventory.push_back("shield");

	vector<string>::iterator myIterator; // scrivibile
	vector<string>::const_iterator iter; // durante la visita le informazioni del vettore non possono cambiate, sono trattate come costanti

	PrintInventory(inventory, iter);

	//MaddoLib::Output("your items: ");
	//for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
	//	MaddoLib::OutputLine(*iter); // puntatore di deferenziazione, permette di accedere al contenuto della cella
	//}

	MaddoLib::OutputLine("You trade your sword for a battle axe");
	myIterator = inventory.begin();
	*myIterator = "battle axe";
	PrintInventory(inventory, iter);


	MaddoLib::OutputLine("armor breaks");

}


void HighScores() {
	vector<int>::const_iterator iter;

	MaddoLib::OutputLine("creating list of scores");

}

void hangaman() {
	const int MAX_WRONG = 8;

	vector<string> words;
	words.push_back("GUESS");
	words.push_back("HANGMAN");
	words.push_back("DIFFICULT");

	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(words.begin(), words.end());
	//string myWord = *words.begin();

	//MaddoLib::OutputLine(myWord);

	const string THE_WORD = words[0];
	int wrong = 0;
	string soFar(THE_WORD.size(), '-');
	string used = "";

	MaddoLib::OutputLine("Welcome to hangman");

	while ((wrong < MAX_WRONG) && (soFar != THE_WORD)) {

	}

	if (wrong == MAX_WRONG) {
		MaddoLib::OutputLine("Impiccherino");
	}
	else {
		MaddoLib::OutputLine("Vinto");
	}
}