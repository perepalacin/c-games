#include "./controls.h"
#include "../game-history/game-history.h"
#include "../game-loop/game-loop.h"
#include "raylib.h"
#include <stdio.h>

// TODO: wrap everything in a handle user input

bool isDraggingPiece = false;

void handleKeyboardNavigation(void) {
    if (IsKeyPressed(KEY_TAB) && IsKeyDown(KEY_LEFT_SHIFT)) {
        selectPreviousPiece();
    } else if (IsKeyPressed(KEY_TAB)) {
        selectNextPiece();
    } else if (IsKeyPressed(KEY_J)) {
        revertMove();
    } else if (IsKeyPressed(KEY_K)) {
        forwardMove();
    }
}

void handleMouseNavigation(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectPieceByCoordinates(GetMousePosition());
    }
}

void handlePieceMouseMovement(void) {
    if (!isDraggingPiece && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // Start dragging
        isDraggingPiece = true;
    } else if (isDraggingPiece && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // Dragging
    } else if (isDraggingPiece && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // Release
        isDraggingPiece = false;
        handleReleasePiece(GetMousePosition());
    }
}
