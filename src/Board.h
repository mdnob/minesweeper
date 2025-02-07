#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <cstdlib>
#include <ctime>

struct Tile
{
    bool mine = false;
    int value = 0;
    bool reveal = false;
    bool flag = false;
    std::vector<Tile*> neighbors;

    void recursiveReveal()
    {
        for(Tile* tile: neighbors)
        {
            if(tile->reveal == true || tile->flag == true) continue;
            tile->reveal = true;
            if(tile->value > 0) continue;
            tile->recursiveReveal();
        }
    }
};

class Board
{
public:
    void ReadFile(std::string path);
    void Neighbors();
    std::vector<Tile>& GetBoard();
    int neighborMines(int& row, int& column);
    bool winning();
    bool won();
    int getMines();
    int getFlags();
    int& getRows();
    int& getCols();

    void newGame(int& mines);
    void clearBoard();

    void setRows(int rows);
    void setColumns(int columns);
    void setReveal(int& row, int& column);
    void setFlag(int& row, int& column, bool flag);
    void setDebug(bool debug);
    void revealMines();
    void flagMines();

    bool getDebug();

    void PrintBoard();
private:
    int rows;
    int columns;
    bool debug = false;
    std::vector<Tile> board;
};

#endif // BOARD_H_INCLUDED
