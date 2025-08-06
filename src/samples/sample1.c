#include "../entities/particle.h"
#include "../utils/vectors.h"
 
Particle *particles;

const int PARTICLES_COUNT = 50;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Particle *InitParticles(void) {
    Particle *particles = (Particle *)malloc(PARTICLES_COUNT * sizeof(Particle));
    
    if (particles == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for particles.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0;  i < PARTICLES_COUNT; i++) {
        particles[i] = InitRandomParticle(i); 
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
