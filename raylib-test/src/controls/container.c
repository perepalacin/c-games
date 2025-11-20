#include "container.h"
#include "../main.h"

extern const int CONTAINER_WIDTH;
extern const int CONTAINER_HEIGHT;

extern const int CONTAINER_X_PADDING;
extern const int CONTAINER_Y_PADDING;

const float border_thickness = 3.0f;

void DrawContainer (void) {
    Rectangle container = {CONTAINER_X_PADDING - border_thickness, CONTAINER_Y_PADDING - border_thickness, CONTAINER_WIDTH + border_thickness, CONTAINER_HEIGHT + border_thickness}; 
    DrawRectangleLinesEx(container, border_thickness, RAYWHITE);
}

void HighlightActiveGravity (RectangleSides side) {
    if (side == TOP) {
        DrawLineEx(
            (Vector2){CONTAINER_X_PADDING, CONTAINER_Y_PADDING - border_thickness}, 
            (Vector2){CONTAINER_WIDTH + CONTAINER_X_PADDING, CONTAINER_Y_PADDING - border_thickness},
            border_thickness * 2,
            YELLOW);
    } else if (side == RIGHT) {
        DrawLineEx(
            (Vector2){CONTAINER_WIDTH + CONTAINER_X_PADDING - border_thickness, CONTAINER_Y_PADDING}, 
            (Vector2){CONTAINER_WIDTH + CONTAINER_X_PADDING - border_thickness, CONTAINER_HEIGHT + CONTAINER_Y_PADDING},
            border_thickness * 2,
            YELLOW);
    } else if (side == BOTTOM) {
        DrawLineEx(
            (Vector2){CONTAINER_X_PADDING, CONTAINER_HEIGHT + CONTAINER_Y_PADDING - border_thickness}, 
            (Vector2){CONTAINER_WIDTH + CONTAINER_X_PADDING, CONTAINER_HEIGHT + CONTAINER_Y_PADDING - border_thickness},
            border_thickness * 2,
            YELLOW);
    } else if (side == LEFT) {
        DrawLineEx(
            (Vector2){CONTAINER_X_PADDING - border_thickness, CONTAINER_Y_PADDING }, 
            (Vector2){CONTAINER_X_PADDING - border_thickness, CONTAINER_HEIGHT + CONTAINER_Y_PADDING},
            border_thickness * 2,
            YELLOW);
    }
}