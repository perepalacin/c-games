#ifndef MAP_H

#include "raylib.h"

typedef enum {
    FIELD_DAY,
    FIELD_AFTERNOON,
    FIELD_NIGHT,
    // SURF_DAY,
    // SURF_AFTERNOON,
    // SURF_NIGHT,
    // CITY_DAY,
    // CITY_AFTERNOON,
    // CITY_NIGHT,
    // FOREST_DAY,
    // FOREST_AFTERNOON,
    // FOREST_NIGHT,
    // ROCKY_DAY,
    // ROCKY_AFTERNOON,
    // ROCKY_NIGHT,
    // SNOW_DAY,
    // SNOW_AFTERNOON,
    // SNOW_NIGHT,
    // INDOOR_1,
    // INDOOR_2,
    // INDOOR_3,
    // CAVE_1,
    // CAVE_2,
    // CAVE_3,
    // AARON,
    // BERTHA,
    // FLINT,
    // LUCIAN,
    // CYNTHIA,
    // DISTORTION_WORLD,
    // BATTLE_TOWER,
    // BATTLE_FACTORY,
    // BATTLE_ARCADE,
    // BATTLE_CASTLE,
    // BATTLE_HALL,
    SPRITES_COUNT
} MapSprites;

typedef struct {
    MapSprites mapType;
    Rectangle mapRect;
    Rectangle playerRect;
    Rectangle enemyRect;
} MapSprite;

void initMapSprites(void);
void renderMap(MapSprites);
void unloadMapSprites(void);

#endif
