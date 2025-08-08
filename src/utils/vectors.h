#ifndef VECTORS_H
#define VECTORS_H

#include "raylib.h"
#include <math.h>

float GetDistance (Vector2 v1, Vector2 v2);
float GetModulus(Vector2 v);
Vector2 GetNormalized (Vector2 v);
#endif