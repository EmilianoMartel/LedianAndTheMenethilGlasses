#include <iostream>

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
    bool hasCrystal = false;
};

enum MapOptions {
    Ledian,
    Wall,
    Glasses,
    Box,
    Exit,
    Hole,
    None
};

Tile playerTile;
Tile wallTile;
Tile glassesTile;
Tile boxTile;
Tile exitTile;
Tile holeTile;
Tile noneTile;

MapOptions map[MAX_WIDTH][MAX_HEIGHT]{
    {Wall, Wall, Wall, Wall, Wall, Wall, Wall,None,None,None},
    {Wall, Ledian, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,Wall,Wall,Wall},
    {Wall, Wall, Wall, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, Wall, Wall, Wall,Wall,Wall,Wall},
};

MapOptions originalMap[MAX_WIDTH][MAX_HEIGHT]{
    {Wall, Wall, Wall, Wall, Wall, Wall, Wall,None,None,None},
    {Wall, Ledian, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,None,None,None},
    {Wall, None, None, None, None, None, Wall,Wall,Wall,Wall},
    {Wall, Wall, Wall, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, None, None, None,None,None,Wall},
    {None, None, None, Wall, Wall, Wall, Wall,Wall,Wall,Wall},
};

void ShowMap() {
    for (size_t i = 0; i < MAX_WIDTH; i++)
    {
        cout << endl;
        for (size_t j = 0; j < MAX_HEIGHT; j++)
        {
            switch (map[i][j])
            {
            case Ledian:
                cout << playerTile.graphic << " ";
                break;
            case Wall:
                cout << wallTile.graphic << " ";
                break;
            case Glasses:
                cout << glassesTile.graphic << " ";
                break;
            case Box:
                cout << boxTile.graphic << " ";
                break;
            case Exit:
                cout << exitTile.graphic << " ";
                break;
            case Hole:
                cout << holeTile.graphic << " ";
                break;
            case None:
                cout << noneTile.graphic << " ";
                break;
            default:
                break;
            }
        }
    }
}

int main()
{
    playerTile.graphic = 'X';
    wallTile.graphic = 'X';
    glassesTile.graphic = 'X';
    boxTile.graphic = 'X';
    exitTile.graphic = 'X';
    holeTile.graphic = 'X';
    noneTile.graphic = ' ';

    ShowMap();
}

