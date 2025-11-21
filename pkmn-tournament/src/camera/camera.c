#include "./camera.h"

void initFreeCamera(Camera2D *camera) {
    camera->offset = (Vector2){0, 0};
    // camera->offset = (Vector2){(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    camera->target = (Vector2){0, 0};
    camera->rotation = 0.0f;
    // camera->zoom = 1.0f;
    camera->zoom = SCALING_FACTOR;
}
