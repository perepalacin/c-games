#ifndef MAPS_H
#define MAPS_H

#include "raylib.h"
#include <stdio.h>

typedef struct {
    Rectangle sprite_rectangle;
    int tile_width;
    int tile_height;
} MapTileDefinition;


typedef enum {
    GREEN_TREE_1,
    GREEN_TREE_2,
    GREEN_TREE_3,
    GREEN_TREE_4,
    NUM_TILE_TYPES,
} TileID;

void LoadTileAssets(void);
void UnloadTileAssets(void);

#endif