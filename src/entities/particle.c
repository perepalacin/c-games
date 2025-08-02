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

// We actually need to update both particles
void UpdateParticlesAfterCollision (Particle *p1, Particle *p2) {
    // Momentum is a constant
    // float momentumX = p1->weight*GetModulus(p1->speed) + p2->weight*GetModulus(p2->speed);
    float momentum_x = p1->weight * p1->speed.x + p2->weight * p2->speed.x;
    float momentum_y = p1->weight * p1->speed.y + p2->weight * p2->speed.y;


}

void RenderParticle (Particle particle) {
    printf("Rendering particle with coordinates -> x: %f, y: %f and id: %d\n", particle.centerPos.x, particle.centerPos.x, particle.id);
    DrawCircleV(particle.centerPos, particle.radius, particle.color);                              
    if (particle.thickness != 0.0f) {
        DrawCircleV(particle.centerPos, particle.radius - particle.thickness, BACKGROUND_COLOR);                              
    }
}