#include "./menus.h"
#include "../camera/camera.h"
#include "raylib.h"
#include <stdlib.h>

typedef enum { FIGHT, BAG, RUN, PKMN, POSITION_COUNT } MainMenuPositions;

Texture2D menuTextures;
static bool isTextureLoaded = false;
static MainMenuPositions menuPosition = FIGHT;

typedef struct {
    Rectangle selectorRect;
    Vector2 selectorTarget;
} MenuSelectorSprites;

MenuSelectorSprites menuSelectorSprites[POSITION_COUNT] = {
    {
        .selectorRect = {294, 41, 218, 92},
        .selectorTarget = {0, 0},
    },
    //    {
    //        .selectorRect = {294, 41 +98, 126, 57}, // Move selector
    //    },
    {
        .selectorRect = {294, 41 + 161, 80, 46},
        .selectorTarget = {0, 0},
    }};

void loadMenuSprites(void) {
    menuTextures = LoadTexture("images/combat-sprites.png");
    isTextureLoaded = true;
}

void renderMainCombatMenu(void) {
    if (!isTextureLoaded) {
        exit(132);
    }
    Rectangle menuRect = {17, 35, SCREEN_WIDTH, 203};
    Vector2 menuTargetPosition = {0.0f, 197};
    DrawTextureRec(menuTextures, menuRect, menuTargetPosition, WHITE);
    DrawTextureRec(menuTextures, menuSelectorSprites[menuPosition].selectorRect,
                   menuSelectorSprites[menuPosition].selectorTarget, WHITE);
}

void unloadMenuSprites(void) {
    UnloadTexture(menuTextures);
    isTextureLoaded = false;
}
