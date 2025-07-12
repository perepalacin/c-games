#include "raylib.h"
#include "entities/player.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int TARGET_FPS = 60;
const int TILE_SIZE = 20; // size in pixels!
Player g_player;

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Game Test");
    initPlayer(&g_player, (Vector2){5, 5}); 

    SetTargetFPS(TARGET_FPS);
    
    loadPlayerSprites();

    while (!WindowShouldClose())
    {
        float delta_time = GetFrameTime();

        if (IsKeyDown(KEY_W)) {
            g_player.current_animation = PLAYER_ANIM_WALK_UP;
            g_player.pixel_pos.y -= 100.0f * delta_time;
        } else {
             g_player.current_animation = PLAYER_ANIM_IDLE_DOWN; 
        }

        updatePlayerAnimation(&g_player, delta_time);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawPlayer(&g_player, g_player.pixel_pos);

        EndDrawing();
    }

    unloadPlayerSprites();
    CloseWindow();

    return 0;
}