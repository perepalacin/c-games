
#include "entities/player.h"
#include "graphics/camera.h"
#include "world/maps.h"
#include "main.h"


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
    InitMap();
    SetTargetFPS(TARGET_FPS);
    LoadPlayerTextures();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        RenderMap();
        UpdateFreeCamera();
        UpdatePlayerState();
        DrawPlayer();
        EndMode2D();
        EndDrawing();
    }

    FreeMap();
    UnloadTileAssets();
    CloseWindow();

    return 0;
}