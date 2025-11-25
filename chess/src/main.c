#include "./board/board.h"
#include "game-loop/game-loop.h"
#include "raylib.h"
#define TARGET_FPS 60

Camera2D camera = {.offset = {0, 0}, .target = {0, 0}, .rotation = 0, .zoom = SCALING_FACTOR};

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess game");
    SetTargetFPS(TARGET_FPS);
    loadSprites();
    initGame();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        mainGameLoop();
        EndMode2D();
        EndDrawing();
    }
    unloadSprites();
    return 0;
}
