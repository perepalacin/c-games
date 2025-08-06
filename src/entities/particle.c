#include "particle.h"
#include "../utils/vectors.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern Color BACKGROUND_COLOR;

const int MAX_X_SPEED = 4;
const int MAX_Y_SPEED = 4;

Particle InitParticle (Vector2 centerPos, Vector2 speed, float radius, Color color, float thickness) {
    return (Particle){
        .centerPos = centerPos,
        .speed = speed,
        .radius = radius,
        .color = color,
        .thickness = thickness
    };
}

void SetParticleColorBasedOnSpeed(Particle *particle) {
    const float speed_modulus = GetModulus(particle->speed);
    const float max_speed = GetModulus((Vector2){MAX_X_SPEED, MAX_Y_SPEED});
    particle->color = (Color){ (int)(speed_modulus/(max_speed)*255) , 0, 255 - ((int)(speed_modulus/(max_speed)*255)), 255 };
}

Particle InitRandomParticle (int id) {
    Particle newParticle;
    newParticle.id = id;
    newParticle.centerPos = (Vector2){ (float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT) }; 
    newParticle.speed = (Vector2){ (float)GetRandomValue(-MAX_X_SPEED, MAX_X_SPEED), (float)GetRandomValue(-MAX_Y_SPEED, MAX_Y_SPEED) }; 
    newParticle.radius = (float)GetRandomValue(1, 4);
    newParticle.thickness = 0;
    newParticle.weight = (float)GetRandomValue(0, 8);  
    SetParticleColorBasedOnSpeed(&newParticle);
    return newParticle;
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
    SetParticleColorBasedOnSpeed(p1);
    SetParticleColorBasedOnSpeed(p2);
}


void RenderParticle (Particle particle) {
    DrawCircleV(particle.centerPos, particle.radius, particle.color);                              
    if (particle.thickness != 0.0f) {
        DrawCircleV(particle.centerPos, particle.radius - particle.thickness, BACKGROUND_COLOR);                              
    }
}