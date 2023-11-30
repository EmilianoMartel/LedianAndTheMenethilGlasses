#include <iostream>
#include <Windows.h>
#include <sstream>
#include <conio.h>

#define MAX_WIDTH 10
#define MAX_HEIGHT 10

using namespace std;

//Const
const string TITLE = "Lidian and the Menethil Glasses";

struct Vector2 {
	int X = 0;
	int Y = 0;
	void print() {
		cout << "Position is = " << X << " " << Y << endl;
	}
} position;

struct Tile {
	Vector2 position;
	char graphic = 'X';
	bool hasPlayer = false;
	bool hasGlasses = false;
	bool hasBox = false;
	bool hasExit = false;
};

struct MoveCharacter {
	Vector2 position;
	Tile graphic;
	bool hasGlasses = false;
}player;

enum MapOptions {
	Ledian,
	Wall,
	Glasses,
	Box,
	Exit,
	Hole,
	None
};

struct MapStruct {
	Tile tile;
	MapOptions mapOption;
};

//GraphicMap
Tile playerTile;
Tile wallTile;
Tile glassesTile;
Tile boxTile;
Tile exitTile;
Tile holeTile;
Tile noneTile;

int boxCount = 0;

Vector2 tempPosition;
int inputOption = 1;
bool rePlay = true;
int turnsCount = 0;

MapOptions originalMap[MAX_WIDTH][MAX_HEIGHT]{
	{Wall, Wall, Wall, Wall, Wall, Wall, Wall,None,None,None},
	{Wall, Ledian, None, None, None, Exit, Wall,None,None,None},
	{Wall, None, None, None, None, None, Wall,None,None,None},
	{Wall, Hole, None, Hole, None, Hole, Wall,None,None,None},
	{Wall, None, None, None, Box, None, Wall,Wall,Wall,Wall},
	{Wall, None, None, Box, None, None, Hole,None,None,Wall},
	{Wall, Wall, Wall, Wall, Hole, None, None,None,None,Wall},
	{None, None, None, Wall, None, Box, None,None,Hole,Wall},
	{None, None, None, Wall, None, None, None,Hole,Glasses,Wall},
	{None, None, None, Wall, Wall, Wall, Wall,Wall,Wall,Wall},
};

MapStruct map[MAX_WIDTH][MAX_HEIGHT];

int CheckIntInput(int cant) {
	string input;
	bool inputValue = false;
	int inputNum = 1;

	do {
		cout << "Enter a option: " << endl;
		getline(cin, input);

		istringstream stream(input);

		if (stream >> inputNum) {
			inputValue = true;
			if (inputNum > cant) {
				cout << "The input is out of range. Please try again" << endl;
				inputValue = false;
			}
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!inputValue);

	return inputNum;
}

void PressAnyButton() {
	cout << "Press any key to continue..." << endl;
	getchar();
	system("cls");
}

char GetInput() {
	if (_kbhit()) {
		return _getch();
	}
	return '0';
}

void ProcessInput(char input) {
	switch (input)
	{
	case 'w':
		turnsCount++;
		if (tempPosition.Y > 0) {
			tempPosition.Y -= 1;
		}
		break;
	case 'a':
		turnsCount++;
		if (tempPosition.X > 0) {
			tempPosition.X -= 1;
		}
		break;
	case 's':
		turnsCount++;
		if (tempPosition.Y < MAX_HEIGHT) {
			tempPosition.Y += 1;
		}
		break;
	case 'd':
		turnsCount++;
		if (tempPosition.X < MAX_WIDTH) {
			tempPosition.X += 1;
		}
		break;
	default:
		break;
	}
}

void SetMap() {
	turnsCount = 0;
	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			map[i][j].tile.position.X = j;
			map[i][j].tile.position.Y = i;
			switch (originalMap[i][j])
			{
			case Ledian:
				player.position.X = j;
				player.position.Y = i;
				tempPosition = player.position;
				map[i][j].tile.graphic = noneTile.graphic;
				map[i][j].tile.hasPlayer = true;
				map[i][j].mapOption = MapOptions::Ledian;
				break;
			case Wall:
				map[i][j].tile.graphic = wallTile.graphic;
				map[i][j].mapOption = MapOptions::Wall;
				break;
			case Box:
				map[i][j].tile.graphic = noneTile.graphic;
				map[i][j].mapOption = MapOptions::Box;
				map[i][j].tile.hasBox = true;
				break;
			case Glasses:
				map[i][j].tile.graphic = glassesTile.graphic;
				map[i][j].mapOption = MapOptions::Glasses;
				map[i][j].tile.hasGlasses = true;
				break;
			case Exit:
				map[i][j].tile.graphic = exitTile.graphic;
				map[i][j].tile.hasExit = true;
				map[i][j].mapOption = MapOptions::Exit;
				break;
			case Hole:
				map[i][j].tile.graphic = holeTile.graphic;
				map[i][j].mapOption = MapOptions::Hole;
				break;
			case None:
				map[i][j].tile.graphic = noneTile.graphic;
				map[i][j].mapOption = MapOptions::None;
				break;
			default:
				break;
			}
			if (map[i][j].tile.position.X == player.position.X && map[i][j].tile.position.Y == player.position.Y) {
				map[i][j].tile.hasPlayer = true;
			}
			else {
				map[i][j].tile.hasPlayer = false;
			}
		}
	}
}

void ShowMap() {
	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		cout << endl;
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			if (map[i][j].tile.hasBox) {
				cout << boxTile.graphic << " ";
			}
			else if (map[i][j].tile.hasPlayer) {
				cout << player.graphic.graphic << " ";
			}
			else if (map[i][j].tile.hasGlasses && player.hasGlasses) {
				cout << noneTile.graphic << " ";
			}
			else if (map[i][j].tile.hasExit && !player.hasGlasses) {
				cout << noneTile.graphic << " ";
			}
			else {
				cout << map[i][j].tile.graphic << " ";
			}
		}
	}
}

void Replay() {
	int reReplayChoose;
	cout << "¿Play again?." << endl;
	cout << "1 - RePlay" << endl;
	cout << "2 - Back to menu" << endl;
	cout << "3 - Exit" << endl;
	reReplayChoose = CheckIntInput(3);
	switch (reReplayChoose)
	{
	case 1:
		SetMap();
		cout << "Okey! Good luck!" << endl;
		PressAnyButton();
		rePlay = true;
		break;
	case 2:
		rePlay = false;
		cout << "Back to menu." << endl;
		PressAnyButton();
		break;
	case 3:
		rePlay = false;
		inputOption = 3;
		break;
	default:
		break;
	}
}

void WinOrLoseLogic(string logic) {
	rePlay = false;
	if (logic == "win") {
		cout << "Congratulations, you win!" << endl;
	}
	else {
		cout << "You fail the mission." << endl;
	}
	cout << turnsCount << "stepts" << endl;
	Replay();
}

void MoveCheck() {
	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		cout << endl;
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			if (map[i][j].tile.position.X == tempPosition.X && map[i][j].tile.position.Y == tempPosition.Y) {
				char tipeTile = map[i][j].tile.graphic;
				Vector2 temp = player.position;
				temp.X -= tempPosition.X;
				temp.Y -= tempPosition.Y;
				switch (map[i][j].mapOption)
				{
				case Wall:
					tempPosition = player.position;
					break;
				case Glasses:
					player.hasGlasses = true;
					player.position = map[i][j].tile.position;
					break;
				case Exit:
					player.position = map[i][j].tile.position;
					if (player.hasGlasses) {
						WinOrLoseLogic("win");
					}
					break;
				case Hole:
					if (map[i][j].tile.hasBox) {
						player.position = map[i][j].tile.position;
					}
					else {
						WinOrLoseLogic("lose");
					}
					break;
				case None:
					player.position = map[i][j].tile.position;
					break;
				default:
					break;
				}
				if (map[i][j].tile.hasBox && tempPosition.X == map[i][j].tile.position.X && tempPosition.Y == map[i][j].tile.position.Y) {
					if (map[i - temp.Y][j - temp.X].mapOption == MapOptions::Wall) {
						tempPosition = player.position;
					}
					else if (map[i - temp.Y][j - temp.X].mapOption == MapOptions::None && !map[i - temp.Y][j - temp.X].tile.hasBox) {
						player.position = map[i][j].tile.position;
						map[i][j].tile.hasBox = false;
						map[i - temp.Y][j - temp.X].tile.hasBox = true;
					}
					else if(map[i - temp.Y][j - temp.X].mapOption == MapOptions::Hole){
						player.position = map[i][j].tile.position;
						map[i][j].tile.hasBox = false;
						map[i - temp.Y][j - temp.X].mapOption = MapOptions::None;
						map[i - temp.Y][j - temp.X].tile.graphic = noneTile.graphic;
					}
				}
				if (map[i][j].tile.position.X == player.position.X && map[i][j].tile.position.Y == player.position.Y) {
					map[i][j].tile.hasPlayer = true;
				}
				else {
					map[i][j].tile.hasPlayer = false;
				}
			}
		}
	}
}

void Game() {
	while (rePlay) {
		system("cls");
		ShowMap();
		ProcessInput(GetInput());
		MoveCheck();
		Sleep(100);
	}
}

void Intro() {
	cout << "A long time ago, a group of sorcerers hid a powerful artifact in the depths of the ruins of Daeron." << endl;
	cout << "This artifact was a pair of glasses that granted the wearer the ability to see new worlds invisible to the human eye." << endl;
	cout << "They belonged to an old king, who haves his life for your people and the legend tells that the forests cry when he dies." << endl;
	cout << "Ledian first heard this story during one of his adventures, and today he sets out in search of this mysterious object." << endl;
	PressAnyButton();
}

void Instructions() {
		system("cls");
		cout << "Your mission is to take the Glasses(G) and escape the dungeon." << endl;
		cout << "You can move with W A S D." << endl;
		cout << "When you dont have a Glasses(G), you cant see the exist(E)." << endl;
		cout << "If you falling in a hole(O), you lose immediately." << endl;
		cout << "You can push the boxes(X) to hole(O) to cover they." << endl;
		PressAnyButton();

}

int main()
{
	playerTile.graphic = 'L';
	wallTile.graphic = 'W';
	glassesTile.graphic = 'G';
	boxTile.graphic = 'X';
	exitTile.graphic = 'E';
	holeTile.graphic = 'O';
	noneTile.graphic = ' ';

	player.graphic = playerTile;

	SetMap();

	cout << TITLE << endl;
	Intro();
	do
	{
		system("cls");
		cout << TITLE << endl;
		cout << "Play" << endl;
		cout << "Instructions" << endl;
		cout << "Exit" << endl;
		inputOption = CheckIntInput(3);
		switch (inputOption)
		{
		case 1:
			SetMap();
			Game();
			break;
		case 2:
			break;
		default:
			break;
		}
	} while (inputOption != 3);

}

