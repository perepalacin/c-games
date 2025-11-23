#include "./dialog.h"
#include "camera.h"
#include "raylib.h"
#include <stdlib.h>

Texture2D dialogBubbleTexture;
static bool isTextureLoaded = false;

void loadDialogSprites(void) {
    // TODO: replace this texture with the actual texture!
    dialogBubbleTexture = LoadTexture("images/sprites/dialog-box.png");
    isTextureLoaded = true;
}

void renderDialogBubble(void) {
    if (!isTextureLoaded) {
        exit(132);
    }
    Rectangle dialogRect = {0, 0, 252, 44};
    Vector2 dialogTargetPosition = {2, 152};
    DrawRectangle(0, 151, 256, 46, BLACK);
    DrawTextureRec(dialogBubbleTexture, dialogRect, dialogTargetPosition, WHITE);
}

void unloadDialogSprites(void) {
    UnloadTexture(dialogBubbleTexture);
    isTextureLoaded = false;
}
