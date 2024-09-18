#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
using namespace std;

class Block
{
private:
    int cellSize;
    int rotationState;
    vector<Color> colors;

public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int row, int col);
    vector<Position> getCellPositions();
    void Rotate();
    int id;
    int rowOffset;
    int colOffset;
    map<int, vector<Position>> cells;
};