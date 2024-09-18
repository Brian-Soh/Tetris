#pragma once
#include <vector>
#include <raylib.h>
using namespace std;

class Grid
{

private:
    int numRows;
    int numCols;
    int cellSize;
    bool isRowFull(int row);
    vector<Color> colors;
    void clearRow(int row);
    void moveRowDown(int row, int magnitude);

public:
    Grid();
    void Initialize();
    void Draw();
    void Print();
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    int clearFullRows();
    int grid[20][10];
};