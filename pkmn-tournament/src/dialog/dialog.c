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
    Rectangle menuRect = {0, 0, 252, 44};
    Vector2 menuTargetPosition = {2, 152};
    DrawTextureRec(dialogBubbleTexture, menuRect, menuTargetPosition, WHITE);
}

void unloadDialogSprites(void) {
    UnloadTexture(dialogBubbleTexture);
    isTextureLoaded = false;
}
