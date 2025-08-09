#include "../entities/particle.h"
#include "../utils/vectors.h"
 
Particle *particles;

extern const int CONTAINER_WIDTH;
extern const int CONTAINER_HEIGHT;

const int ROWS_OF_PARTICLES = 20;
const int COLS_OF_PARTICLES = 30;

Particle *InitParticles(void) {
    Particle *particles = (Particle *)malloc(ROWS_OF_PARTICLES * COLS_OF_PARTICLES * sizeof(Particle));
    
    if (particles == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for particles.\n");
        exit(EXIT_FAILURE);
    }

    // TODO: Tonight, fix the initial position of the particle!
    int temp_id = 0;
    for (int i = 0;  i < COLS_OF_PARTICLES; i++) {
        for (int j = 0; j < ROWS_OF_PARTICLES; j++) {
            particles[temp_id] = InitParticle(
                temp_id,
                (Vector2){(float)(CONTAINER_WIDTH / (COLS_OF_PARTICLES + 1)) * (i + 1), (CONTAINER_HEIGHT / (float)(ROWS_OF_PARTICLES + 1)) * (j + 1)},
                (Vector2){0.0f, 0.0f},
                (Vector2){0.0f, 0.0f},
                5.0f,
                0.0f,
                (float)GetRandomValue(1, 100));
            temp_id++;
        }
    }

    return particles;
}

void DeinitParticles(Particle *particles) {
    if (particles != NULL) {
        free(particles);
        particles = NULL; 
    }
}

void DetectCollissions (Particle *particle, Particle *particles) {
    for (int i = 0; i < ROWS_OF_PARTICLES * COLS_OF_PARTICLES; i++) {
        if (particles[i].id == particle->id) {
            continue;
        }

        if (GetDistance(particles[i].centerPos, particle->centerPos) <= (particles[i].radius + particle->radius)) {
            UpdateParticlesAfterCollision(particle, &particles[i]);
        }
    }
}

void UpdateParticles(Particle *particles) {
    for (int i = 0; i < ROWS_OF_PARTICLES * COLS_OF_PARTICLES; i++) {
        AddMouseInteractivity(&particles[i]);
        AddParticleGravity(&particles[i]);
        UpdateParticle(&particles[i]);
        DetectCollissions(&particles[i], particles);
        UpdateParticlesColors(particles, ROWS_OF_PARTICLES * COLS_OF_PARTICLES);
        RenderParticle(particles[i]);
    }
}
