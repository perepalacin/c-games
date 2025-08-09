#ifndef CONTAINER_H
#define CONTAINER_H

#include "raylib.h"

typedef enum {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
} RectangleSides;

void DrawContainer (void);
void HighlightActiveGravity (RectangleSides side);

#endif