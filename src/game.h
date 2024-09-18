#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
private:
    vector<Block> blocks;
    vector<Block> newBlocks;
    Block currentBlock;
    Block nextBlock;
    Block savedBlock;
    Grid grid;
    Block getRandomBlock();
    vector<Block> getAllBlocks();
    void moveBlockLeft();
    void moveBlockRight();
    bool isBlockOutside();
    void rotateBlock();
    void dropBlock();
    void lockBlock();
    void saveBlock();
    void Reset();
    void updateScore(int linesCleared, int moveDownPoints);

public:
    Game();
    void Draw();
    void handleInput();
    void moveBlockDown();
    bool blockCollision();
    bool gameOver;
    int score;
};