#include "./camera/camera.h"
#include "./combat/combat.h"
#include "./map/map.h"
#include "./menus/menus.h"
#include "dialog/dialog.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Camera2D camera = {0};
const Color BACKGROUND_COLOR = BLACK;

int main(void) {
    srand(time(0));
    InitWindow(SCREEN_WIDTH * SCALING_FACTOR, SCREEN_HEIGHT * SCALING_FACTOR, "Pkmn Tournament");
    SetTargetFPS(TARGET_FPS);
    initFreeCamera(&camera);
    initMapSprites();
    loadMenuSprites();
    loadCombatTextures();
    loadDialogSprites();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        BeginMode2D(camera);
        renderMap(FIELD_NIGHT);
        renderCombat();
        renderDialogBubble();
        EndMode2D();
        EndDrawing();
    }
    unloadDialogSprites();
    unloadMapSprites();
    unloadMenuSprites();
    unloadCombatTextures();
    return 0;
}
