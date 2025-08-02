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
void UpdateParticlesAfterCollision(Particle *p1, Particle *p2) {
    // --- 1. Get initial velocity components and masses ---
    float v1ix = p1->speed.x;
    float v1iy = p1->speed.y;
    float v2ix = p2->speed.x;
    float v2iy = p2->speed.y;

    float m1 = p1->weight;
    float m2 = p2->weight;

    // --- 2. Determine the line of impact (angle phi) ---
    // The line of impact is the line connecting the centers of the two particles
    // at the moment of collision. This line defines the 'normal' direction.
    float deltaX = p2->centerPos.x - p1->centerPos.x;
    float deltaY = p2->centerPos.y - p1->centerPos.y;

    // Calculate the angle of this normal vector with respect to the positive x-axis.
    // atan2f handles all quadrants correctly.
    float phi = atan2f(deltaY, deltaX);

    // --- 3. Resolve Initial Velocities into Normal (n) and Tangential (t) Components ---
    // The normal component is along the line of impact (angle phi).
    // The tangential component is perpendicular to the line of impact (phi - 90 degrees).

    // Components for Particle 1
    float v1in = v1ix * cosf(phi) + v1iy * sinf(phi); // Initial normal velocity of p1
    float v1it = -v1ix * sinf(phi) + v1iy * cosf(phi); // Initial tangential velocity of p1

    // Components for Particle 2
    float v2in = v2ix * cosf(phi) + v2iy * sinf(phi); // Initial normal velocity of p2
    float v2it = -v2ix * sinf(phi) + v2iy * cosf(phi); // Initial tangential velocity of p2

    // --- 4. Calculate Final Normal Components (1D elastic collision formulas) ---
    // For an elastic collision, the coefficient of restitution (e) is 1.0.
    float e = 1.0f;

    // These formulas are derived from 1D conservation of momentum and coefficient of restitution.
    float v1fn = ((m1 - e * m2) * v1in + (1.0f + e) * m2 * v2in) / (m1 + m2);
    float v2fn = ((m2 - e * m1) * v2in + (1.0f + e) * m1 * v1in) / (m1 + m2);

    // --- 5. Final Tangential Components ---
    // In an elastic collision (and without friction), tangential components remain unchanged.
    float v1ft = v1it;
    float v2ft = v2it;

    // --- 6. Reconstruct Final Cartesian Components ---
    // Convert the normal and tangential final velocities back into x and y components
    // using the angle 'phi'.

    p1->speed.x = v1fn * cosf(phi) - v1ft * sinf(phi);
    p1->speed.y = v1fn * sinf(phi) + v1ft * cosf(phi);

    p2->speed.x = v2fn * cosf(phi) - v2ft * sinf(phi);
    p2->speed.y = v2fn * sinf(phi) + v2ft * cosf(phi);

    // The 'momentumX' and 'momentumY' variables from your initial snippet
    // represent the *initial total momentum*. They are not used to *update* the particles,
    // but rather are conserved by the physics formulas applied above.
    // You could calculate them here and compare to initial values to verify conservation.
    // float final_momentum_x = p1->weight * p1->speed.x + p2->weight * p2->speed.x;
    // float final_momentum_y = p1->weight * p1->speed.y + p2->weight * p2->speed.y;
    // These should be equal to the initial momentum values (within floating point precision).
}


void RenderParticle (Particle particle) {
    printf("Rendering particle with coordinates -> x: %f, y: %f and id: %d\n", particle.centerPos.x, particle.centerPos.x, particle.id);
    DrawCircleV(particle.centerPos, particle.radius, particle.color);                              
    if (particle.thickness != 0.0f) {
        DrawCircleV(particle.centerPos, particle.radius - particle.thickness, BACKGROUND_COLOR);                              
    }
}