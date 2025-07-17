#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "entities/player.h"
#include "graphics/camera.h"
#include "main.h"
// #include "raymath.h"


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 720;
const int GRID_SIZE = 20;
const Vector2 screenSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
const int TARGET_FPS = 60;
Camera2D camera = { 0 };

int main(void)
{
	srand(time(0));
    InitFreeCamera();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Game Test");

    SetTargetFPS(TARGET_FPS);
    LoadPlayerTextures();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        UpdateFreeCamera();
        UpdatePlayerState();
        DrawPlayer();
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}