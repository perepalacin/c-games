#include "particle.h"
#include "../utils/vectors.h"
#include <math.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TARGET_FPS;
extern Color BACKGROUND_COLOR;

const bool is_friction_active = 1;

const int MAX_X_SPEED = 250;
const int MAX_Y_SPEED = 250;

int logs = 500;

Color GetColorBasedOnSpeed(Vector2 speed, const float max_speed) {
    float value = GetModulus(speed);
    const float mid_val = max_speed / 2.0f;

    if (value < 0.0f) value = 0.0f;
    if (value > max_speed) value = max_speed;

    if (mid_val == 0) {
        return (Color){0, 0, 255, 255};
    }

    return (value <= mid_val) 
        ? 
        (Color){
            0,
            (unsigned char)((value / mid_val) * 255.0f),
            (unsigned char)(255 - (value / mid_val) * 255.0f),
            255
        }
        : 
        (Color){
            (unsigned char)(((value - mid_val) / mid_val) * 255.0f),
            255,
            0,
            255
        };
}

// try to implement this without the particles count argument!
void UpdateParticlesColors (Particle *particles, int particles_count) {
    float max_speed = 0;
    for (int i = 0; i < particles_count; i++) {
        if (GetModulus(particles[i].speed) > max_speed) {
            max_speed = GetModulus(particles[i].speed);
        }
    }

    for (int i = 0; i < particles_count; i++) {
        particles[i].color = GetColorBasedOnSpeed(particles[i].speed, max_speed);
    }
}

Particle InitParticle (int id, Vector2 centerPos, Vector2 speed, Vector2 acceleration, float radius, float thickness, float weight) {
    return (Particle){
        .id = id,
        .centerPos = centerPos,
        .speed = speed, // in m/s
        .acceleration =acceleration,
        .radius = radius, // in mm
        .color = GetColorBasedOnSpeed(speed, GetModulus(speed)),
        .thickness = thickness,
        .weight = weight, // in kg
    };
}

Particle InitRandomParticle (int id) {
    Particle newParticle;
    newParticle.id = id;
    newParticle.radius = (float)GetRandomValue(1, 20);
    Vector2 center_pos = (Vector2){ (float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT) }; 
    
    if (center_pos.x - newParticle.radius <= 0) {
        center_pos.x = center_pos.x + newParticle.radius;
    } else if (center_pos.x + newParticle.radius >= SCREEN_WIDTH) {
        center_pos.x = center_pos.x - newParticle.radius;
    }
    
    if (center_pos.y - newParticle.radius <= 0) {
        center_pos.y = center_pos.y + newParticle.radius;
    } else if (center_pos.y + newParticle.radius >= SCREEN_HEIGHT) {
        center_pos.y = center_pos.y - newParticle.radius;
    }

    newParticle.centerPos = center_pos;
    newParticle.speed = (Vector2){ (float)GetRandomValue(-MAX_X_SPEED, MAX_X_SPEED), (float)GetRandomValue(-MAX_Y_SPEED, MAX_Y_SPEED) }; 
    newParticle.acceleration = (Vector2) {0.0f, 0.0f};
    newParticle.thickness = 0;
    newParticle.weight = (float)GetRandomValue(1, 100);  
    newParticle.color = GetColorBasedOnSpeed(newParticle.speed, GetModulus(newParticle.speed));
    return newParticle;
}

void AddParticleGravity(Particle *particle) {
    float deltaTime = GetFrameTime();

    bool is_gravity_active = 0;

    float gravity_constant = 1000.0f;
    float gravity_magnitude = (gravity_constant * particle->weight);
        
    Vector2 gravity_direction;

    if (IsKeyDown(KEY_UP)) {
        gravity_direction = (Vector2){0.0f, -1.0f};
    } else if (IsKeyDown(KEY_LEFT)) {
        gravity_direction = (Vector2){-1.0f, 0.0f};
    } else if (IsKeyDown(KEY_RIGHT)) {
        gravity_direction = (Vector2){1.0f, 0.0f};
    } else if (IsKeyDown(KEY_DOWN)) {
        gravity_direction = (Vector2){0.0f, 1.0f};
    } else {
        gravity_direction = (Vector2){0.0f, 0.0f};
    }

    if (gravity_direction.x == 0 && gravity_direction.y == 0) {
        return;
    }

    Vector2 gravity_force = {gravity_magnitude * gravity_direction.x, gravity_magnitude * gravity_direction.y};

    Vector2 gravity_acceleration = {gravity_force.x / particle->weight, gravity_force.y / particle->weight};

    particle->speed.x += gravity_acceleration.x * deltaTime;
    particle->speed.y += gravity_acceleration.y * deltaTime;
}

void AddMouseInteractivity(Particle *particle) {
    Vector2 mouse_position = GetMousePosition();
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return;

    if (mouse_position.x > 0 
    && mouse_position.x < SCREEN_WIDTH
    && mouse_position.y > 0 &&
    mouse_position.y < SCREEN_HEIGHT ) {
        float deltaTime = GetFrameTime();

        Vector2 delta = {particle->centerPos.x - mouse_position.x, particle->centerPos.y - mouse_position.y};
        
        float gravity_constant = 6230000.0f; // G * M2 
        float gravity_magnitude = (gravity_constant * particle->weight) / (GetModulus(delta) * GetModulus(delta));
        
        Vector2 attraction_direction = GetNormalized((Vector2){delta.x, delta.y});
        
        if (IsKeyDown(KEY_R)) {
            attraction_direction.x *= -1;
            attraction_direction.y *= -1;
        }

        Vector2 attraction_force = {gravity_magnitude * attraction_direction.x, gravity_magnitude * attraction_direction.y};

        Vector2 attraction_acceleration = {attraction_force.x / particle->weight, attraction_force.y / particle->weight};

        particle->speed.x += attraction_acceleration.x * deltaTime;
        particle->speed.y += attraction_acceleration.y * deltaTime;

    }
}

void CheckBoundaryCollisions (Particle *particle) {
    float deltaTime = GetFrameTime();
    if (((particle->centerPos.x + particle->speed.x * deltaTime + particle->radius) >= SCREEN_WIDTH) || 
    ((particle->centerPos.x + particle->speed.x * deltaTime - particle->radius) <= 0)) {
        particle->speed.x *= -1;
    }

    if (((particle->centerPos.y + particle->speed.y * deltaTime + particle->radius) >= SCREEN_HEIGHT) || 
    ((particle->centerPos.y + particle->speed.y * deltaTime - particle->radius) <= 0)) {
        particle->speed.y *= -1;
    }
}

void ApplyParticleDrag (Particle *particle) {
    float deltaTime = GetFrameTime();
    const float friction_coefficient = 0.5f;
    const float air_density = 120.0f;
    const float drag_coefficient = 1.17f;
    float particle_surface = PI * (particle->radius/1000) * (particle->radius/1000); 

    float speed_modulus = GetModulus(particle->speed);
    float friction_magnitude = friction_coefficient * air_density * speed_modulus * speed_modulus * drag_coefficient * particle_surface;
    Vector2 friction_direction = GetNormalized(particle->speed);
    friction_direction.x *= -1;
    friction_direction.y *= -1;
        
    Vector2 friction_force = {friction_direction.x * friction_magnitude, friction_direction.y * friction_magnitude};
        
    Vector2 friction_acceleration = {friction_force.x / particle->weight, friction_force.y / particle->weight};
        
    particle->speed.x += friction_acceleration.x * deltaTime;
    particle->speed.y += friction_acceleration.y * deltaTime;

    // Debug to see if i can remove this!
    if (GetModulus(particle->speed) < 0.1f) {
        particle->speed = (Vector2){0, 0};
    }
}

void UpdateParticle(Particle *particle) {
    float deltaTime = GetFrameTime();

    CheckBoundaryCollisions(particle);
    
    if (is_friction_active && GetModulus(particle->speed) != 0) {
        ApplyParticleDrag(particle);
    }

    particle->centerPos.x += particle->speed.x * deltaTime;
    particle->centerPos.y += particle->speed.y * deltaTime;
}   

void UpdateParticlesAfterCollision(Particle *p1, Particle *p2) {
    float v1ix = p1->speed.x;
    float v1iy = p1->speed.y;
    float v2ix = p2->speed.x;
    float v2iy = p2->speed.y;

    float m1 = p1->weight;
    float m2 = p2->weight;

    Vector2 delta = {p2->centerPos.x - p1->centerPos.x, p2->centerPos.y - p1->centerPos.y};

    float phi = atan2f(delta.y, delta.x);

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
    p1->acceleration = (Vector2){0.0f, 0.0f};

    p2->speed.x = v2fn * cosf(phi) - v2ft * sinf(phi);
    p2->speed.y = v2fn * sinf(phi) + v2ft * cosf(phi);
    p2->acceleration = (Vector2){0.0f, 0.0f};

    float distance = GetDistance(p1->centerPos, p2->centerPos);
    float overlap = (p1->radius + p2->radius) - distance;

    if (overlap > 0) {
        Vector2 collisionNormal = GetNormalized(delta);
        float totalMass = m1 + m2;
        float p1MoveAmount = overlap*1.1f * (m2 / totalMass);
        float p2MoveAmount = overlap*1.1f * (m1 / totalMass);

        p1->centerPos.x -= collisionNormal.x * p1MoveAmount;
        p1->centerPos.y -= collisionNormal.y * p1MoveAmount;

        p2->centerPos.x += collisionNormal.x * p2MoveAmount;
        p2->centerPos.y += collisionNormal.y * p2MoveAmount;
    }
}


void RenderParticle (Particle particle) {
    if (logs < 500) {
        ++logs;
    }
    DrawCircleV(particle.centerPos, particle.radius, particle.color);                              
    if (particle.thickness != 0.0f) {
        DrawCircleV(particle.centerPos, particle.radius - particle.thickness, BACKGROUND_COLOR);                              
    }
}