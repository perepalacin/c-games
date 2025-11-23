#include "./menus.h"
#include "../camera/camera.h"
#include "raylib.h"
#include <stdlib.h>

typedef enum {
    MAIN_MENU_FIGHT_POS,
    MAIN_MENU_BAG_POS,
    MAIN_MENU_RUN_POS,
    MAIN_MENU_PKMN_POS,
    MAIN_MENU_POSITION_COUNT
} MainMenuPositions;

typedef enum {
    FIGHT_MENU_MOV_1,
    FIGHT_MENU_MOV_2,
    FIGHT_MENU_MOV_3,
    FIGHT_MENU_MOV_4,
    FIGHT_MENU_CANCEL,
    FIGHT_MENU_POSITION_COUNT
} FightMenuPositions;

typedef enum {
    MENU_MAIN_STATE,
    MENU_FIGHT_STATE,
    MENU_BAG_STATE,
    MENU_PKMN_STATE,
    MENU_STATE_COUNT
} MainMenuStates;

typedef struct {
    MainMenuPositions currentPos;
    MainMenuPositions previousPos;
} MainMenuPosition;

typedef struct {
    FightMenuPositions currentPos;
    FightMenuPositions previousPos;
} FightMenuPosition;

Texture2D menuTextures;
static bool isTextureLoaded = false;

static MainMenuStates menuState = MENU_MAIN_STATE;
static MainMenuPosition mainMenuPosition = {
    .currentPos = MAIN_MENU_FIGHT_POS,
    .previousPos = MAIN_MENU_POSITION_COUNT,
};

static FightMenuPosition fightMenuPosition = {
    .currentPos = FIGHT_MENU_MOV_1,
    .previousPos = FIGHT_MENU_POSITION_COUNT,
};

typedef struct {
    Rectangle selectorRect;
    Vector2 selectorTarget;
} MenuSelectorSprites;

MenuSelectorSprites mainMenuSelectorSprites[MAIN_MENU_POSITION_COUNT] = {
    {
        .selectorRect = {294, 41, 218, 92},
        .selectorTarget = {19, 233},
    },
    //    {
    //        .selectorRect = {294, 41 +98, 126, 57}, // Move selector
    //    },
    {
        .selectorRect = {294, 41 + 161, 80, 46},
        .selectorTarget = {0, 344},
    },
    {
        .selectorRect = {294, 41 + 161, 80, 46},
        .selectorTarget = {88, 352},
    },
    {
        .selectorRect = {294, 41 + 161, 80, 46},
        .selectorTarget = {176, 344},
    }};

MenuSelectorSprites fightMenuSelectorSprites[FIGHT_MENU_POSITION_COUNT] = {
    {
        .selectorRect = {294, 139, 126, 57},
        .selectorTarget = {1, 197 + 23},
    },
    {
        .selectorRect = {294, 139, 126, 57},
        .selectorTarget = {129, 197 + 23},
    },
    {
        .selectorRect = {294, 139, 126, 57},
        .selectorTarget = {1, 197 + 85},
    },
    {
        .selectorRect = {294, 139, 126, 57},
        .selectorTarget = {129, 197 + 85},
    },
    {
        .selectorRect = {295, 255, 238, 47},
        .selectorTarget = {9, 197 + 156},
    }};

void loadMenuSprites(void) {
    menuTextures = LoadTexture("images/combat-sprites.png");
    isTextureLoaded = true;
}

void unloadMenuSprites(void) {
    UnloadTexture(menuTextures);
    isTextureLoaded = false;
}

static void updateMainMenuPosition(void) {
    if (IsKeyPressed(KEY_UP)) {
        if (mainMenuPosition.currentPos != MAIN_MENU_FIGHT_POS) {
            mainMenuPosition.previousPos = mainMenuPosition.currentPos;
            mainMenuPosition.currentPos = MAIN_MENU_FIGHT_POS;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        if (mainMenuPosition.currentPos == MAIN_MENU_PKMN_POS) {
            mainMenuPosition.currentPos = MAIN_MENU_RUN_POS;
        } else if (mainMenuPosition.currentPos == MAIN_MENU_RUN_POS) {
            mainMenuPosition.currentPos = MAIN_MENU_BAG_POS;
        }
    } else if (IsKeyPressed(KEY_RIGHT)) {
        if (mainMenuPosition.currentPos == MAIN_MENU_BAG_POS) {
            mainMenuPosition.currentPos = MAIN_MENU_RUN_POS;
        } else if (mainMenuPosition.currentPos == MAIN_MENU_RUN_POS) {
            mainMenuPosition.currentPos = MAIN_MENU_PKMN_POS;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        if (mainMenuPosition.currentPos == MAIN_MENU_FIGHT_POS) {
            if (mainMenuPosition.previousPos != MAIN_MENU_POSITION_COUNT) {
                mainMenuPosition.currentPos = mainMenuPosition.previousPos;
            } else {
                mainMenuPosition.currentPos = MAIN_MENU_BAG_POS;
            }
        }
    }
}

static void updateMainMenuState(void) {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        if (mainMenuPosition.currentPos == MAIN_MENU_FIGHT_POS) {
            menuState = MENU_FIGHT_STATE;
        } else if (mainMenuPosition.currentPos == MAIN_MENU_BAG_POS) {
            menuState = MENU_BAG_STATE;
        } else if (mainMenuPosition.currentPos == MAIN_MENU_RUN_POS) {
            // TODO: you can't exit trainer battles
        } else if (mainMenuPosition.currentPos == MAIN_MENU_PKMN_POS) {
            menuState = MENU_PKMN_STATE;
        }
    } else if (IsKeyPressed(KEY_ESCAPE) && menuState != MENU_MAIN_STATE) {
        menuState = MENU_MAIN_STATE;
        mainMenuPosition.currentPos = MAIN_MENU_FIGHT_POS;
        mainMenuPosition.previousPos = MAIN_MENU_POSITION_COUNT;
    }
}

static void updateFightMenuPosition(void) {
    if (IsKeyPressed(KEY_RIGHT)) {
        if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_1) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_2;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_1;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_3) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_4;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_3;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_2) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_1;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_2;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_4) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_3;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_4;
        }
    } else if (IsKeyPressed(KEY_UP)) {
        if (fightMenuPosition.currentPos == FIGHT_MENU_CANCEL) {
            fightMenuPosition.currentPos = fightMenuPosition.previousPos;
            fightMenuPosition.previousPos = FIGHT_MENU_CANCEL;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_3) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_1;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_3;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_4) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_2;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_4;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_1) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_3;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_1;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_2) {
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_4;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_2;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_3) {
            fightMenuPosition.currentPos = FIGHT_MENU_CANCEL;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_3;
        } else if (fightMenuPosition.currentPos == FIGHT_MENU_MOV_4) {
            fightMenuPosition.currentPos = FIGHT_MENU_CANCEL;
            fightMenuPosition.previousPos = FIGHT_MENU_MOV_4;
        }
    } else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        if (fightMenuPosition.currentPos == FIGHT_MENU_CANCEL) {
            menuState = MENU_MAIN_STATE;
            mainMenuPosition.currentPos = MAIN_MENU_FIGHT_POS;
            mainMenuPosition.previousPos = MAIN_MENU_POSITION_COUNT;
            fightMenuPosition.currentPos = FIGHT_MENU_MOV_1;
            fightMenuPosition.previousPos = FIGHT_MENU_POSITION_COUNT;
        }
    }
}

void renderMainCombatMenu(Pokemon *pokemon) {
    if (!isTextureLoaded || pokemon == NULL) {
        exit(132);
    }
    Vector2 menuTargetPosition = {0.0f, 197};
    if (menuState == MENU_MAIN_STATE) {
        Rectangle menuRect = {17, 35, SCREEN_WIDTH, 203};
        DrawTextureRec(menuTextures, menuRect, menuTargetPosition, WHITE);
        DrawTextureRec(menuTextures,
                       mainMenuSelectorSprites[mainMenuPosition.currentPos].selectorRect,
                       mainMenuSelectorSprites[mainMenuPosition.currentPos].selectorTarget, WHITE);
        DrawTextureRec(menuTextures,
                       mainMenuSelectorSprites[mainMenuPosition.currentPos].selectorRect,
                       mainMenuSelectorSprites[mainMenuPosition.currentPos].selectorTarget, WHITE);
        updateMainMenuPosition();
        updateMainMenuState();
    } else if (menuState == MENU_FIGHT_STATE) {
        Rectangle menuRect = {17, 248, SCREEN_WIDTH, 203};
        DrawTextureRec(menuTextures, menuRect, menuTargetPosition, WHITE);
        DrawTextureRec(
            menuTextures, fightMenuSelectorSprites[fightMenuPosition.currentPos].selectorRect,
            fightMenuSelectorSprites[fightMenuPosition.currentPos].selectorTarget, WHITE);
        updateFightMenuPosition();
    }
}
