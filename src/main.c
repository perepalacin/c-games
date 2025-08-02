
#include "entities/player.h"
#include "graphics/camera.h"
#include "world/maps.h"
#include "main.h"


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 720;
const Vector2 screenSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
const int TARGET_FPS = 60;
Camera2D camera = { 0 };

int main(void)
{
	srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Game Test");
    InitFreeCamera();
    LoadMap();
    SetTargetFPS(TARGET_FPS);
    LoadPlayerTextures();

    while (!WindowShouldClose()) {
        UpdateFreeCamera();
        UpdatePlayerState();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
            RenderMap();
        EndMode2D();
        EndDrawing();
    }

    UnloadMap();
    CloseWindow();

    return 0;
}