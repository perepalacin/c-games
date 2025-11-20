#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int id;
    Vector2 centerPos;
    Vector2 speed;
    Vector2 acceleration;
    float radius;
    Color color;
    float thickness;
    float weight;
} Particle;

Particle InitParticle (int id, Vector2 centerPos, Vector2 speed, Vector2 acceleration, float radius, float thickness, float weight);
Particle InitRandomParticle (int id);
void RenderParticle(Particle);
void UpdateParticle(Particle *);
void UpdateParticlesColors (Particle *particles, int particles_count);
void AddParticleGravity(Particle *);
void AddMouseInteractivity(Particle *particle);
void UpdateParticlesAfterCollision(Particle *p1, Particle *p2);
#endif