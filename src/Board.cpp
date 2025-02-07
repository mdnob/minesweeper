#include "Board.h"

void Board::ReadFile(std::string path)
{
    std::ifstream file;
    file.open(path);
    std::string line;

    board.clear();
    char c;
    while (file.get(c))
    {
        if(c == '\n') continue;
        Tile tile;
        if(c == '1'){
            tile.mine = true;
        }
        board.push_back(tile);
    }
    file.close();
    Neighbors();
}

void Board::Neighbors()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            Tile* tile = &board[i * columns + j];
            tile->neighbors.clear();
            // up left
            if(i - 1 >= 0 && j - 1 >= 0) tile->neighbors.push_back(&board[(i - 1) * columns + (j - 1)]);

            // up
            if(i - 1 >= 0) tile->neighbors.push_back(&board[(i - 1) * columns + j]);

            // up right
            if(i - 1 >= 0 && j + 1 < columns) tile->neighbors.push_back(&board[(i - 1) * columns + (j + 1)]);

            // left
            if(j - 1 >= 0) tile->neighbors.push_back(&board[i * columns + (j - 1)]);

            // right
            if(j + 1 < columns) tile->neighbors.push_back(&board[i * columns + (j + 1)]);

            // down left
            if(i + 1 < rows && j - 1 >= 0) tile->neighbors.push_back(&board[(i + 1) * columns + (j - 1)]);

            // down
            if(i + 1 < rows) tile->neighbors.push_back(&board[(i + 1) * columns + j]);

            // down right
            if(i + 1 < rows && j + 1 < columns) tile->neighbors.push_back(&board[(i + 1) * columns + (j + 1)]);

            // adjacent mines count
            tile->value = neighborMines(i, j);
        }
    }
}

std::vector<Tile>& Board::GetBoard()
{
    return board;
}

int Board::neighborMines(int& row, int& column)
{
    int count = 0;
    for(Tile* tile : board[row * columns + column].neighbors)
    {
        if(tile->mine == 1) count++;
    }
    return count;
}

bool Board::winning()
{
    for(Tile& tile : board)
    {
        if(tile.mine == true && tile.reveal == true) return false;
    }
    return true;
}

bool Board::won()
{
    for(Tile& tile : board)
    {
        if(tile.mine == true && tile.reveal == true) return false;
        else if(tile.mine == false && tile.reveal == false) return false;
    }
    return true;
}

int Board::getMines()
{
    int count = 0;
    for(Tile& tile : board)
    {
        if(tile.mine == true ) count++;
    }
    return count;
}

int Board::getFlags()
{
    int count = 0;
    for(Tile& tile : board)
    {
        if(tile.flag == true ) count++;
    }
    return count;
}

int& Board::getRows()
{
    return rows;
}

int& Board::getCols()
{
    return columns;
}

void Board::clearBoard()
{
    board.clear();
    for(int i = 0; i < rows * columns; i++)
    {
        Tile tile;
        board.push_back(tile);
    }
}

void Board::newGame(int& mines)
{
    int rand_num;

    static std::mt19937 random(time(0));
    std::uniform_int_distribution<int> dist(0, rows * columns);

    clearBoard();

    for(int i = 0; i < mines && i <= rows * columns; i++)
    {
        rand_num = dist(random);
        while(board[rand_num].mine == true)
        {
            rand_num = dist(random);
        }
        board[rand_num].mine = true;
    }

    Neighbors();
}

void Board::setRows(int rows)
{
    this->rows = rows;
}

void Board::setColumns(int columns)
{
    this->columns = columns;
}

void Board::setReveal(int& row, int& column)
{
    Tile* tile = &board[row * columns + column];
    if(row < rows && column < columns && tile->reveal == false && tile->flag == false)
    {
        tile->reveal = true;
        if(tile->mine == false && tile->value == 0)
        {
            tile->recursiveReveal();
        }
        else if(tile->mine == true)
        {
            revealMines();
        }
    }
}

void Board::setFlag(int& row, int& column, bool flag)
{
    if(row < rows && column < columns)
    {
        Tile* tile = &board[row * columns + column];
        if(tile->reveal == false) tile->flag = flag;
    }
}

void Board::setDebug(bool debug)
{
    this->debug = debug;
}

bool Board::getDebug()
{
    return debug;
}

void Board::revealMines()
{
    for(Tile& tile : board)
    {
        if(tile.mine == true)
        {
            tile.reveal = true;
        }
    }
}

void Board::flagMines()
{
    for(Tile& tile : board)
    {
        if(tile.mine == true)
        {
            tile.flag = true;
        }
    }
}

void Board::PrintBoard()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            std::cout << board[i * columns + j].mine;
        }
        std::cout << std::endl;
    }
}
