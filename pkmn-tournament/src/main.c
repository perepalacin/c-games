#include "./camera/camera.h"
#include "./map/map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Camera2D camera = {0};
const Color BACKGROUND_COLOR = BLACK;

int main(void) {
    srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pkmn Tournament");
    SetTargetFPS(TARGET_FPS);
    initFreeCamera(&camera);
    initMapSprites();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        BeginMode2D(camera);
        renderMap(FIELD_NIGHT);
        EndMode2D();
        EndDrawing();
    }

    unloadMapSprites();
    return 0;
}
