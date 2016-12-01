// Esercizio2.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "MaddoLib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>
using namespace std;
using namespace Maddo;
//Dichiarazione funzioni
enum Marker { empty = 0, treasure = 1, wall = 2, trap = 5, hero = 7 };
enum Direction { up, down, left, right, invalid };

//class Vector2
//{
//public:
//	int x, y;
//
//};

const int GRID_SIZE = 25;
const int GRID_WIDTH = 5;
void Game();
int Move(int originalPosition, vector<int>& grid);
bool IsCellFree(vector<int> grid, int cell);
Marker GetCell(vector<int> grid, int cell);
string MarkerToChar(Marker marker);
Direction ValidateDirection(string s);
void GenerateMarkers(vector<int>& grid, Marker marker, int amount);
void PrintGrid(vector<int> grid, bool showAll);



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
	int playerPosition;
	//int playerColumn = 3;
	//grid[12] = Marker::hero;

	//GenerateMarkers(grid);
	GenerateMarkers(grid, Marker::trap, 3);
	GenerateMarkers(grid, Marker::treasure, 1);
	GenerateMarkers(grid, Marker::hero, 1);
	playerPosition = find(grid.begin(), grid.end(), Marker::hero);

	while (true)
	{
		MaddoLib::ClearScreen();
		PrintGrid(grid, true);
		playerPosition = Move(playerPosition, grid); // todo: controllo trappole o tesori
	}

	//auto p = pair(1, 1);


}

int Move(int originalPosition, vector<int>& grid)
{
	Direction direction;
	string d;
	int destination;
	bool isValid = false;
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
			isValid = destination >= 0;
		}
		else if (direction == Direction::down)
		{
			destination = originalPosition + GRID_WIDTH;
			isValid = destination < GRID_SIZE;
		}
		else if (direction == Direction::right)
		{
			destination = originalPosition + 1;		
			isValid = (destination % 5) > 0;
		}
		else if (direction == Direction::left)
		{
			destination = originalPosition - 1;
			isValid = ((destination % 5) < GRID_WIDTH -1) && destination >= 0;
		}
		
		if (isValid && IsCellFree(grid, destination))
		{
			grid[originalPosition] = Marker::empty;
			grid[destination] = Marker::hero;
			return destination;
		}

		// Validazione destinazione
		/*if (destination < 0 || destination >= GRID_SIZE ||(destination % 5 != originalPosition % 5))
		{
			MaddoLib::OutputLine("Posizione non valida");
		}
		else if (!IsCellFree(grid, destination)) {
			MaddoLib::OutputLine("Non è possibile muoversi in quella direzione");
		}
		else
		{
			grid[originalPosition] = Marker::empty;
			grid[destination] = Marker::hero;
			return destination;
		}*/
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

string CellToChar(vector<int> grid, int cell)
{


	return string();
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


void GenerateMarkers(vector<int>& grid, Marker marker, int amount)
{
	int pos;
	int failsafe = 0;
	for (int i = 0; i < amount; i++)
	{
		while (failsafe < 9000)
		{
			pos = rand() % GRID_SIZE;
			if (IsCellFree(grid, pos))
			{
				grid[pos] = marker;
				break;
			}
			failsafe++;
		}
	}
}

string MarkerToChar(Marker marker)
{
	if (marker == Marker::empty)
	{
		return ".";
	}
	else if (marker == Marker::hero)
	{
		return "@";
	}
	else if (marker == Marker::trap)
	{
		return "^";
	}
	else if (marker == Marker::treasure)
	{
		return ")";
	}
	else if (marker == Marker::wall)
	{
		return "X";
	}
	else return "-"; // failsafe
}

void PrintGrid(vector<int> grid, bool showAll)
{
	int i = 0;
	int j = 0;
	string m;
	for (auto & cell : grid)
	{

		m = MarkerToChar(GetCell(grid, i));
		MaddoLib::Output(m);

		j++;
		if (j >= GRID_WIDTH)
		{
			MaddoLib::OutputLine();
			j = 0;
		}
		i++;

	}
}
