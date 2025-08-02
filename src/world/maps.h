#ifndef MAPS_H
#define MAPS_H

#include <stdbool.h>
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef enum {
    GREEN_TREE_1,
    GREEN_TREE_2,
    GREEN_TREE_3,
    GREEN_TREE_4,
    GRASS_TILE_1,
    NUM_TILE_TYPES,
} TileID;

typedef enum {
    EVENT_NONE,
    EVENT_SPAWN,
} EventId;

typedef struct {
    Rectangle sprite_rectangle;
    Vector2 sprite_origin;
    int tile_width;
    int tile_height;
    int tile_id;
    bool is_walkable;
    int event_id;   
} MapTileDefinition;

typedef struct {
    MapTileDefinition ground_layer;  
    MapTileDefinition folliage_layer;
    MapTileDefinition object_layer;  
    // could add the weather layer for clouds, rain and such
} MapCell;

void LoadMap(void);
void RenderMap(void);
void UnloadMap(void);
#endif