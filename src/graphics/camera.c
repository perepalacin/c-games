#include "../main.h"
#include "camera.h"
#include "../entities/player.h"

int camera_x_pos;
int camera_y_pos;
float camera_zoom;
int is_camera_in_freemode;
extern Camera2D camera; 

void InitFreeCamera () {
    camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 };
    camera.target = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1;
}

void UpdateFreeCamera () {
    if (is_camera_in_freemode) {
        if (IsKeyDown(KEY_UP)) {
            camera_y_pos-=10;
        } else if (IsKeyDown(KEY_RIGHT)) {
            camera_x_pos+=10;
        } else if (IsKeyDown(KEY_DOWN)) {
            camera_y_pos+=10;
        } else if (IsKeyDown(KEY_LEFT)) {
            camera_x_pos-=10;
        } else if (IsKeyDown(KEY_Z)) {
            camera_zoom+=0.1f;
        } else if (IsKeyDown(KEY_X)) {
            camera_zoom-=0.1f;
        } else if (IsKeyPressed(KEY_F)) {
            is_camera_in_freemode = 0;
        }
        camera.target = (Vector2){ camera_x_pos, camera_y_pos };
        camera.zoom = camera_zoom;
    } else {
        // TODO: add a debounce or smth + fix initial position of the free camera!
        Vector2 player_pos = GetPlayerPosition();
        camera_x_pos = player_pos.x;
        camera_y_pos = player_pos.y;
        camera.target = (Vector2){ player_pos.x, player_pos.y };
        camera.zoom = camera_zoom = 2;
        if (IsKeyPressed(KEY_F)) {
            is_camera_in_freemode = 1;
            camera_zoom = 1;
        }
    }
}