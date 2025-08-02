#include "main.h"
#include "./entities/particle.h"
#include "./samples/samples.h"


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 720;
const Vector2 screenSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
const int TARGET_FPS = 120;
const Color BACKGROUND_COLOR = BLACK;

Camera2D camera = { 0 };

Particle *particles;

void InitFreeCamera () {
    camera.offset = (Vector2){0,0};
    camera.target = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1;
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
        UpdateParticles(particles);
        EndMode2D();
        EndDrawing();
    }

    return 0;
}