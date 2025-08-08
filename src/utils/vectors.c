#include "vectors.h"

float GetDistance (Vector2 v1, Vector2 v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrtf(dx * dx + dy * dy);
}   

float GetModulus(Vector2 v) {
    if ((v.x * v.x + v.y * v.y) <= 0) {
        return 0;
    } 
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vector2 GetNormalized (Vector2 v) {
    float modulus = GetModulus(v);
    if (modulus == 0.0f) {
        return (Vector2){0.0f, 0.0f};
    }

    return (Vector2){v.x/modulus, v.y/modulus};
}