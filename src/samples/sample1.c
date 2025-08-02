#include "../entities/particle.h"
#include "../utils/vectors.h"
 
Particle *particles;

const int PARTICLES_COUNT = 350;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Particle *InitParticles(void) {
    Particle *particles = (Particle *)malloc(PARTICLES_COUNT * sizeof(Particle));
    
    if (particles == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for particles.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0;  i < PARTICLES_COUNT; i++) {
        particles[i].id = i;
        particles[i].centerPos = (Vector2){ (float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT) }; 
        particles[i].speed = (Vector2){ (float)GetRandomValue(-4, 4), (float)GetRandomValue(-4, 4) }; 
        particles[i].radius = (float)GetRandomValue(1, 4);
        particles[i].color = WHITE;
        // particles[i].color = (Color){ (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 }; 
        particles[i].thickness = 0;
        // particles[i].thickness = (float)GetRandomValue(0, 4) > 2 ? (float)GetRandomValue(2, 4) : 0; 
        particles[i].weight = 1.0f;   
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
    for (int i = 0; i < PARTICLES_COUNT; i++) {
        if (particles[i].id == particle->id) {
            continue;
        }

        if (GetDistance(particles[i].centerPos, particle->centerPos) <= (particles[i].radius + particle->radius)) {
            UpdateParticlesAfterCollision(particle, &particles[i]);
        }
    }
}

void UpdateParticles(Particle *particles) {
    for (int i = 0; i < PARTICLES_COUNT; i++) {
        UpdateParticle(&particles[i]);
        DetectCollissions(&particles[i], particles);
        RenderParticle(particles[i]);
    }
}
