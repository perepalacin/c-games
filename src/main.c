#include "main.h"
#include "./entities/particle.h"
#include "./samples/samples.h"
#include "./controls/container.h"

const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 800;

const int CONTAINER_X_PADDING = 20;
const int CONTAINER_Y_PADDING = 20;
const int CONTAINER_WIDTH = 1100;
const int CONTAINER_HEIGHT = SCREEN_HEIGHT - (CONTAINER_Y_PADDING * 2);

const Vector2 screenSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
const int TARGET_FPS = 120;
const Color BACKGROUND_COLOR = BLACK;

Camera2D camera = { 0 };

Particle *particles;

void InitFreeCamera () {
    camera.offset = (Vector2){0,0};
    camera.target = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

int main(void)
{
	srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Physics Engine");
    SetTargetFPS(TARGET_FPS);
    InitFreeCamera();
    particles = InitParticles();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        BeginMode2D(camera);
        DrawContainer();
        UpdateParticles(particles);
        EndMode2D();
        EndDrawing();
    }

    return 0;
}