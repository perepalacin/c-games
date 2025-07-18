#include "../main.h"
#include "camera.h"

int camera_x_pos;
int camera_y_pos;
float camera_zoom;
extern Camera2D camera; 

void InitFreeCamera () {
    camera_x_pos = SCREEN_WIDTH/2;
    camera_y_pos = SCREEN_HEIGHT/2;
    camera_zoom = 1;
    camera.target = (Vector2){ camera_x_pos, camera_y_pos };
    camera.offset = (Vector2){ camera_x_pos / 2, camera_y_pos / 2 };
    camera.rotation = 0.0f;
    camera.zoom = camera_zoom;
}

void UpdateFreeCamera () {
    if (IsKeyDown(KEY_UP)) {
        camera_y_pos+=10;
    } else if (IsKeyDown(KEY_RIGHT)) {
        camera_x_pos-=10;
    } else if (IsKeyDown(KEY_DOWN)) {
        camera_y_pos-=10;
    } else if (IsKeyDown(KEY_LEFT)) {
        camera_x_pos+=10;
    } else if (IsKeyDown(KEY_Z)) {
        camera_zoom+=0.1f;
    } else if (IsKeyDown(KEY_X)) {
        camera_zoom-=0.1f;
    }
    camera.offset = (Vector2){ camera_x_pos, camera_y_pos };
    camera.zoom = camera_zoom;
}