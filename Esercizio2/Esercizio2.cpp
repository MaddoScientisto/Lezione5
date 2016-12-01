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
enum Marker { empty = 0, treasure = 1, wall = 2, enemy = 3, trap = 5, hero = 7 };
enum Direction { up, down, left, right, invalid };
enum GameState { play, win, loss, lossEnemy };
enum Difficulty { veryEasy = 0, easy = 1, hard = 2, JUST = 3 };
//class Vector2
//{
//public:
//	int x, y;
//
//};

const int GRID_SIZE = 25;
const int GRID_WIDTH = 5;
void Game();
int CheckMovement(int originalPosition, vector<int> grid, bool isPlayer);
bool IsCellFree(vector<int> grid, int cell, bool forPlayer);
Marker GetCell(vector<int> grid, int cell);
string MarkerToChar(Marker marker, bool reveal);
Direction GetRandomDirection();
Direction ValidateDirection(string s);
void GenerateMarkers(vector<int>& grid, Marker marker, int amount);
void PrintGrid(vector<int> grid, bool showAll);
GameState GetGameState(vector<int> grid, int cell);
Difficulty AskForDifficulty();
void GenerateObstacles(vector<int>& grid, Difficulty difficulty);
int FindMarkerPosition(vector<int> grid, int startPosition, Marker marker);
vector<int> FindAllEnemies(vector<int> grid);
void MoveEnemies(vector<int> grid, vector<int>& enemies);
bool IsEnemyOverPlayer(vector<int> grid, vector<int> enemies, int playerPosition);
void UpdateEnemiesPositions(vector<int>& grid, vector<int> enemies);
void ClearMarker(vector<int>& grid, Marker marker);
// Funzioni

int main()
{
	srand(static_cast<unsigned int>(0)); // Inizializzare il generatore di numeri casuali
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
	GameState gameState;
	int tpos; // Temp player position
	
	Difficulty difficulty = AskForDifficulty();
	bool reveal = (difficulty < Difficulty::easy);
	GenerateObstacles(grid, difficulty);

	//auto it = find(grid.begin(), grid.end(), Marker::hero) - grid.begin();
	playerPosition = FindMarkerPosition(grid, 0, Marker::hero); //it;// grid(it);

	vector<int> enemies;

	if (difficulty >= hard)
	{
		enemies = FindAllEnemies(grid);
	}

	while (true)
	{
		MaddoLib::ClearScreen();
		PrintGrid(grid, reveal);
		tpos = CheckMovement(playerPosition, grid, true);

		gameState = GetGameState(grid, tpos);

		if (difficulty >= Difficulty::hard)
		{
			MoveEnemies(grid, enemies);
			if (IsEnemyOverPlayer(grid, enemies, tpos))
			{
				gameState = GameState::lossEnemy;
			}
		}



		if (gameState == GameState::play)
		{
			// Movimento nella nuova posizione
			grid[playerPosition] = Marker::empty;
			grid[tpos] = Marker::hero;
			playerPosition = tpos;

			UpdateEnemiesPositions(grid, enemies);
		}
		else if (gameState == GameState::win)
		{
			MaddoLib::ClearScreen();
			PrintGrid(grid, true);
			MaddoLib::OutputLine("Hai trovato il tesoro! Hai vinto!");
			break;
		}
		else if (gameState == GameState::loss)
		{
			MaddoLib::ClearScreen();
			PrintGrid(grid, true);
			MaddoLib::OutputLine("Sei caduto in una trappola! GAME OVER.");
			break;
		}
		else if (gameState == GameState::lossEnemy)
		{
			MaddoLib::ClearScreen();
			UpdateEnemiesPositions(grid, enemies);
			PrintGrid(grid, true);
			MaddoLib::OutputLine("Sei stato ucciso da un mostro! GAME OVER.");
			break;
		}


	}

	//auto p = pair(1, 1);


}

int CheckMovement(int originalPosition, vector<int> grid, bool isPlayer)
{
	Direction direction;
	string d;
	int destination;
	bool isValid = false;

	while (true)
	{

		if (isPlayer)
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
		}
		else
		{
			// getrandomdirection
			direction = GetRandomDirection();
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
			isValid = ((destination % 5) < GRID_WIDTH - 1) && destination >= 0;
		}

		if (isValid && IsCellFree(grid, destination, isPlayer))
		{
			return destination;
		}

		// se il primo tentativo fallisce (ma la direzione è valida) ed è un npc allora non si muove proprio
		if (isValid && !isPlayer)
		{
			return originalPosition;
		}

	}
}

bool IsCellFree(vector<int> grid, int cell, bool forPlayer)
{
	if (forPlayer)
	{
		return (GetCell(grid, cell) != Marker::wall);
	}
	else
	{
		//return ((GetCell(grid, cell) != Marker::wall) || (GetCell(grid, cell) != Marker::treasure) || (GetCell(grid, cell) != Marker::trap) || (GetCell(grid, cell) != Marker::enemy));
		return ((GetCell(grid, cell) == Marker::hero) || (GetCell(grid, cell) == Marker::empty));
	}

}

Marker GetCell(vector<int> grid, int cell)
{
	return static_cast<Marker>(grid[cell]);
}

string CellToChar(vector<int> grid, int cell)
{
	return string();
}

Direction GetRandomDirection()
{
	int d = rand() % 4;
	return static_cast<Direction>(d);
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
			if (IsCellFree(grid, pos, false))
			{
				grid[pos] = marker;
				break;
			}
			failsafe++;
		}
	}
}

string MarkerToChar(Marker marker, bool reveal)
{
	if (!reveal)
	{
		if (marker == Marker::hero)
		{
			return "@";
		}
		else if (marker == Marker::enemy)
		{
			return "e";
		}
		else if (marker == Marker::wall)
		{
			return "X";
		}
		else
		{
			return ".";
		}
	}

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
	else if (marker == Marker::enemy)
	{
		return "e";
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

		m = MarkerToChar(GetCell(grid, i), showAll);
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

GameState GetGameState(vector<int> grid, int cell)
{

	if (GetCell(grid, cell) == Marker::trap)
	{
		return GameState::loss;
	}
	else if (GetCell(grid, cell) == Marker::treasure)
	{
		return GameState::win;
	}
	else if (GetCell(grid, cell) == Marker::enemy)
	{
		return GameState::lossEnemy;
	}


	return GameState::play;
}

Difficulty AskForDifficulty()
{
	return static_cast<Difficulty> (MaddoLib::InputInt("[0] Facilissimo (no trappole, no nemici, mostra tutto)\n[1] Facile (trappole, no nemici)\n[2] Difficile (no trappole, nemici, muri)\n[3] JUST FUCK MY SHIT UP!! (trappole + nemici + muri)\nScegliere la difficoltà: ", "Scelta errata", 0, 3));
}

void GenerateObstacles(vector<int>& grid, Difficulty difficulty)
{
	GenerateMarkers(grid, Marker::treasure, 1);

	if (difficulty == Difficulty::easy)
	{
		GenerateMarkers(grid, Marker::trap, 3);
	}
	else if (difficulty == Difficulty::hard)
	{
		GenerateMarkers(grid, Marker::wall, 3);
		GenerateMarkers(grid, Marker::enemy, 3);
	}
	else if (difficulty == Difficulty::JUST)
	{
		GenerateMarkers(grid, Marker::trap, 3);
		GenerateMarkers(grid, Marker::wall, 3);
		GenerateMarkers(grid, Marker::enemy, 3);
	}
	GenerateMarkers(grid, Marker::hero, 1);
}

int FindMarkerPosition(vector<int> grid, int startPosition, Marker marker)
{
	auto it = find(grid.begin() + startPosition, grid.end(), Marker::hero) - grid.begin() + startPosition;
	return it;
}

bool IsEnemy(int i)
{
	return i == Marker::enemy;
}

vector<int> FindAllEnemies(vector<int> grid)
{
	vector<int> enemies;
	int i = 0;

	std::vector<int>::iterator iter = grid.begin();
	while ((iter = find_if(iter, grid.end(), IsEnemy)) != grid.end())
	{
		enemies.push_back(iter - grid.begin());

		++iter;
	}

	//while (i < grid.size())
	//{
	//	i = FindMarkerPosition(grid, i, Marker::enemy);
	//	enemies.push_back(i);
	//	i++;
	//}


	return enemies;
}

void MoveEnemies(vector<int> grid, vector<int>& enemies)
{
	//int tMov; // Valore temporaneo
	for (auto & enemy : enemies)
	{
		enemy = CheckMovement(enemy, grid, false);
	}
}

bool IsEnemyOverPlayer(vector<int> grid, vector<int> enemies, int playerPosition)
{
	for (auto & enemy : enemies)
	{
		if (enemy == playerPosition)
		{
			return true;
		}

	}
	return false;
}

void UpdateEnemiesPositions(vector<int>& grid, vector<int> enemies)
{
	ClearMarker(grid, Marker::enemy);
	for (auto & enemy : enemies)
	{
		grid[enemy] = Marker::enemy;
	}
}

void ClearMarker(vector<int>& grid, Marker marker)
{
	for (auto & cell : grid)
	{
		if (cell == marker)
		{
			cell = Marker::empty;
		}
	}
}
