#include "particle.h"
#include "../utils/vectors.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern Color BACKGROUND_COLOR;

Particle InitParticle (Vector2 centerPos, Vector2 speed, float radius, Color color, float thickness) {
    return (Particle){
        .centerPos = centerPos,
        .speed = speed,
        .radius = radius,
        .color = color,
        .thickness = thickness
    };
}

void UpdateParticle(Particle *particle) {
    if (((particle->centerPos.x + particle->speed.x + particle->radius) >= SCREEN_WIDTH) || 
    ((particle->centerPos.x + particle->speed.x - particle->radius) <= 0)) {
        particle->speed.x *= -1;
    }
    if (((particle->centerPos.y + particle->speed.y + particle->radius) >= SCREEN_HEIGHT) || 
    ((particle->centerPos.y + particle->speed.y - particle->radius) <= 0)) {
        particle->speed.y *= -1;
    }
    particle->centerPos.x += particle->speed.x;
    particle->centerPos.y += particle->speed.y;
}   

void UpdateParticlesAfterCollision(Particle *p1, Particle *p2) {
    float v1ix = p1->speed.x;
    float v1iy = p1->speed.y;
    float v2ix = p2->speed.x;
    float v2iy = p2->speed.y;

    float m1 = p1->weight;
    float m2 = p2->weight;

    float deltaX = p2->centerPos.x - p1->centerPos.x;
    float deltaY = p2->centerPos.y - p1->centerPos.y;

    float phi = atan2f(deltaY, deltaX);

    float v1in = v1ix * cosf(phi) + v1iy * sinf(phi);
    float v1it = -v1ix * sinf(phi) + v1iy * cosf(phi);

    float v2in = v2ix * cosf(phi) + v2iy * sinf(phi);
    float v2it = -v2ix * sinf(phi) + v2iy * cosf(phi);

    float e = 1.0f;

    float v1fn = ((m1 - e * m2) * v1in + (1.0f + e) * m2 * v2in) / (m1 + m2);
    float v2fn = ((m2 - e * m1) * v2in + (1.0f + e) * m1 * v1in) / (m1 + m2);

    float v1ft = v1it;
    float v2ft = v2it;

    p1->speed.x = v1fn * cosf(phi) - v1ft * sinf(phi);
    p1->speed.y = v1fn * sinf(phi) + v1ft * cosf(phi);

    p2->speed.x = v2fn * cosf(phi) - v2ft * sinf(phi);
    p2->speed.y = v2fn * sinf(phi) + v2ft * cosf(phi);
}


void RenderParticle (Particle particle) {
    printf("Rendering particle with coordinates -> x: %f, y: %f and id: %d\n", particle.centerPos.x, particle.centerPos.x, particle.id);
    DrawCircleV(particle.centerPos, particle.radius, particle.color);                              
    if (particle.thickness != 0.0f) {
        DrawCircleV(particle.centerPos, particle.radius - particle.thickness, BACKGROUND_COLOR);                              
    }
}