#include "./controls.h"
#include "../game-loop/game-loop.h"
#include "raylib.h"
#include <stdio.h>

// TODO: wrap everything in a handle user input

void handleKeyboardNavigation(void) {
    if (IsKeyPressed(KEY_TAB) && IsKeyDown(KEY_LEFT_SHIFT)) {
        selectPreviousPiece();
    } else if (IsKeyPressed(KEY_TAB)) {
        selectNextPiece();
    }
}

void handleMouseNavigation(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectPieceByCoordinates(GetMousePosition());
    }
}
