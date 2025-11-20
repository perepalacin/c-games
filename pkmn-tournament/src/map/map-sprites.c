#include "./map.h"

MapSprite mapSprites[SPRITES_COUNT] = {
    {
        .mapType = FIELD_DAY,
        .mapRect = {0, 16, 265, 151},
        .playerRect = {256 * 3 + 22, 66, 204, 30}, // offset of x: 63 pixels y: 53 +15
        .enemyRect = {256 * 3 + 65, 24, 126, 32},
    },
    {
        .mapType = FIELD_AFTERNOON,
        .mapRect = {256, 16, 265, 151},
        .playerRect = {256 * 4 + 22, 66, 204, 30},
        .enemyRect = {256 * 4 + 65, 24, 126, 32},
    },
    {
        .mapType = FIELD_NIGHT,
        .mapRect = {512, 16, 265, 151},
        .playerRect = {256 * 5 + 22, 66, 204, 30},
        .enemyRect = {256 * 5 + 65, 24, 126, 32},
    }};
