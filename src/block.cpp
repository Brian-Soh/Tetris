#include "block.h"
#include "colors.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    rowOffset = 0;
    colOffset = 0;
    colors = getCellColors();
}

void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = getCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int row, int col)
{
    rowOffset += row;
    colOffset += col;
}

vector<Position> Block::getCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}
