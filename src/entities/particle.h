#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int id;
    Vector2 centerPos;
    Vector2 speed;
    float radius;
    Color color;
    float thickness;
    float weight;
} Particle;

Particle InitParticle(Vector2 centerPos, Vector2 speed, float radius, Color color, float thickness);
void RenderParticle(Particle);
void UpdateParticle(Particle *);
void UpdateParticlesAfterCollision(Particle *p1, Particle *p2);
#endif