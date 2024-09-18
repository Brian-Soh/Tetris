#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

const Color lightBlue = {59, 85, 162, 255};
const Color darkBlue = {44, 44, 127, 255};

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        if (EventTriggered(0.2))
        {
            game.moveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

        DrawTextEx(font, "Next", {370, 115}, 38, 2, WHITE);
        DrawRectangleRounded({320, 165, 170, 180}, 0.3, 6, lightBlue);

        DrawTextEx(font, "Saved", {355, 355}, 38, 2, WHITE);
        DrawRectangleRounded({320, 395, 170, 180}, 0.3, 6, lightBlue);

        game.Draw();
        game.handleInput();
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {85, 180}, 80, 3, WHITE);
            DrawTextEx(font, "PRESS ENTER", {85, 240}, 65, 3, WHITE);
            DrawTextEx(font, "TO RESTART", {95, 290}, 65, 3, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}