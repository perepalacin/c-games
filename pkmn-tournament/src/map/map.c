#include "./map.h"
#include "../camera/camera.h"
#include <stdlib.h>

Texture2D mapTextures;
bool initializedSprites = false;
extern MapSprite mapSprites[];

void initMapSprites(void) {
    mapTextures = LoadTexture("images/sprites/sprites.png");
    initializedSprites = true;
}

void renderMap(MapSprites mapSprite) {
    if (!initializedSprites) {
        exit(132);
    }
    Vector2 mapTargetPosition = {0.0f, 0.0f};
    DrawTextureRec(mapTextures, mapSprites[mapSprite].mapRect, mapTargetPosition, WHITE);
    Vector2 playerCirclePosition = {-63.0f, ((float)SCREEN_HEIGHT) / 2 -
                                                mapSprites[mapSprite].playerRect.height};
    DrawTextureRec(mapTextures, mapSprites[mapSprite].playerRect, playerCirclePosition, WHITE);
    Vector2 enemyCirclePosition = {129.0f, 72.0f};
    DrawTextureRec(mapTextures, mapSprites[mapSprite].enemyRect, enemyCirclePosition, WHITE);
}

void unloadMapSprites(void) {
    UnloadTexture(mapTextures);
    initializedSprites = false;
}
