#ifndef CAMERA_H
#include "raylib.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 400
#define SCALING_FACTOR 2

#define CONTAINER_X_PADDING 20
#define CONTAINER_Y_PADDING 20
#define CONTAINER_WIDTH 1100
#define CONTAINER_HEIGHT (SCREEN_HEIGHT - (CONTAINER_Y_PADDING * 2))
#define TARGET_FPS 60

void initFreeCamera(Camera2D *camera);

#endif
