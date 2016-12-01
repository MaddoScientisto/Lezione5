// Esercizio2.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "MaddoLib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;
using namespace Maddo;
//Dichiarazione funzioni
enum Marker { empty = 0, treasure = 1, wall = 2, trap = 5, hero = 7 };
enum Direction { up, down, left, right, invalid };
const int GRID_SIZE = 25;
const int GRID_WIDTH = 5;
void Game();
void Move(Direction direction, int originalPosition, vector<int> grid);
bool IsCellFree(vector<int> grid, int cell);
Marker GetCell(vector<int> grid, int cell);
Direction ValidateDirection(string s);
void GenerateMarkers(vector<int>& grid);
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

// 00 01 02 03 04
// 05 06 07 08 09
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24

void Game()
{

	vector<int> grid(GRID_SIZE);
	int playerPosition = 0;

}

void Move(Direction direction, int originalPosition, vector<int> grid)
{
	string d;
	Direction direction;
	int destination;
	while (true)
	{


		while (true)
		{
			d = MaddoLib::Input("Inserire una direzione (w, a, s, d): ");
			direction = ValidateDirection(d);
			if (direction == invalid)
			{
				MaddoLib::OutputLine("Direzione non valida (w, a, s, d).");
			}
			else
			{
				break;
			}
		}

		// Movimento

		if (direction == Direction::up)
		{
			destination = originalPosition - GRID_WIDTH;
		}
		else if (direction == Direction::down)
		{
			destination = originalPosition + GRID_WIDTH;
		}
		else if (direction == Direction::right)
		{
			destination = originalPosition + 1;
		}
		else if (direction == Direction::left)
		{
			destination = originalPosition - 1;
		}
		// Validazione destinazione
		if (destination < 0 || destination >= GRID_SIZE)
		{
			MaddoLib::OutputLine("Posizione non valida");
		}
		else if (!IsCellFree(grid, destination)) {
			MaddoLib::OutputLine("Non è possibile muoversi in quella direzione");
		}
		else 
		{
			break;
		}
	}
}

bool IsCellFree(vector<int> grid, int cell)
{
	return (GetCell(grid, cell) != Marker::wall);
}

Marker GetCell(vector<int> grid, int cell)
{
	return static_cast<Marker>(grid[cell]);

	return Marker();
}

Direction ValidateDirection(string s)
{
	if (s[0] == 'w')
	{
		return Direction::up;
	}
	else if (s[0] == 'a')
	{
		return Direction::left;
	}
	else if (s[0] == 's')
	{
		return Direction::down;
	}
	else if (s[0] == 'd')
	{
		return Direction::right;
	}

	return Direction::invalid;
}

void GenerateMarkers(vector<int>& grid)
{

}
