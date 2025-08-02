#include "vectors.h"

float GetDistance (Vector2 v1, Vector2 v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrtf(dx * dx + dy * dy);
}   

float GetModulus(Vector2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}