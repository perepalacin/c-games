#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "entities/player.h"
#include "main.h"
// #include "raymath.h"


const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 540;
const Vector2 screenSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
const int TARGET_FPS = 60;

int main(void)
{
	srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Game Test");

    SetTargetFPS(TARGET_FPS);
    LoadPlayerTextures();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer();
        // if (IsKeyDown(KEY_W)) {
        //     update_player_sprite();
        // }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}