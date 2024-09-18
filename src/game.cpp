#include "game.h"
#include <random>

Game::Game()
{
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    savedBlock = nullBlock();
    newBlocks = getAllBlocks();
    gameOver = false;
    score = 0;
}

bool Game::isBlockOutside()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (grid.isCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::lockBlock()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (blockCollision())
    {
        gameOver = true;
    }
    nextBlock = getRandomBlock();
    int rowsCleared = grid.clearFullRows();
    updateScore(rowsCleared, 0);
}

void Game::Reset()
{
    grid.Initialize();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    savedBlock = nullBlock();
    score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 800;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}

Block Game::getRandomBlock()
{
    if (blocks.empty())
    {
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::getAllBlocks()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 240);
        break;
    case 4:
        nextBlock.Draw(255, 230);
        break;
    default:
        nextBlock.Draw(270, 220);
        break;
    }

    switch (savedBlock.id)
    {
    case 0:
        break;
    case 3:
        savedBlock.Draw(255, 470);
        break;
    case 4:
        savedBlock.Draw(255, 460);
        break;
    default:
        savedBlock.Draw(270, 450);
        break;
    }
    currentBlock.Draw(11, 11);
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed == KEY_ENTER)
    {
        gameOver = false;
        Reset();
    }
    else if (!gameOver)
    {
        switch (keyPressed)
        {
        case KEY_S:
            saveBlock();
            break;
        case KEY_LEFT:
            moveBlockLeft();
            break;
        case KEY_RIGHT:
            moveBlockRight();
            break;
        case KEY_DOWN:
            moveBlockDown();
            if (!gameOver)
            {
                updateScore(0, 1);
            }
            break;
        case KEY_UP:
            rotateBlock();
            break;
        case KEY_SPACE:
            dropBlock();
            break;
        }
    }
}

void Game::saveBlock()
{
    int id = currentBlock.id;
    if (savedBlock.id == 0)
    {
        savedBlock = newBlocks[id - 1];
        currentBlock = nextBlock;
        nextBlock = getRandomBlock();
    }
    else
    {
        currentBlock = savedBlock;
        savedBlock = newBlocks[id - 1];
    }
}

void Game::dropBlock()
{
    if (!gameOver)
    {
        int points = 0;
        while (!isBlockOutside() && !blockCollision())
        {
            currentBlock.Move(1, 0);
            points++;
        }
        points--;
        currentBlock.Move(-1, 0);
        lockBlock();
        score += points;
    }
}

void Game::moveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (isBlockOutside() || blockCollision())
        {
            currentBlock.Move(0, 1);
        }
    }
}
void Game::moveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (isBlockOutside() || blockCollision())
        {
            currentBlock.Move(0, -1);
        }
    }
}
void Game::moveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (isBlockOutside() || blockCollision())
        {
            currentBlock.Move(-1, 0);
            lockBlock();
        }
    }
}

void Game::rotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (isBlockOutside() || blockCollision())
        {
            currentBlock.Rotate();
            currentBlock.Rotate();
            currentBlock.Rotate();
        }
    }
}

bool Game::blockCollision()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)

    {
        if (grid.isCellEmpty(item.row, item.col) == false)
        {
            return true;
        }
    }
    return false;
}
