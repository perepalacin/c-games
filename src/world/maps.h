#ifndef MAPS_H
#define MAPS_H

#include <stdbool.h>
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct {
    Rectangle sprite_rectangle;
    int tile_width;
    int tile_height;
} MapTileDefinition;

typedef struct {
    int tile_id;
    bool is_walkable;
    int event_id;   
} Tile;

typedef struct {
    Tile ground_layer;    // Base layer: grass, dirt, water
    Tile object_layer;    // Middle layer: trees, rocks, buildings (lower parts)
    Tile overhead_layer;  // Top layer: roofs, bridge tops, tree leaves (drawn above player)
    // You could add more layers for complex scenarios (e.g., shadows, weather effects)
} MapCell;

typedef enum {
    EVENT_NONE,
    EVENT_SPAWN,
} EventId;

typedef enum {
    GREEN_TREE_1,
    GREEN_TREE_2,
    GREEN_TREE_3,
    GREEN_TREE_4,
    GRASS_TILE_1,
    NUM_TILE_TYPES,
} TileID;

typedef struct {
    int key;
    MapTileDefinition* value; 
} MapItem;

typedef struct {
    int size;
    int count;
    MapItem** items;
} MapHashTable;


//TODO: Refactor this mess and remove functions that are not required!
void LoadTileAssets(void);
void InitMap(void);
void RenderMap(void);
void FreeMap(void);
void UnloadTileAssets(void);

unsigned int GenerateHashKey(int x_coord, int y_coord);
static MapHashTable* InitializeMapHashTable(void);
void MapHashTableInsert(MapHashTable* map, const int key, const MapTileDefinition* value);
MapItem* MapHashTableSearch(MapHashTable* map, const int key);
void MapHashTableDelete(MapHashTable* map, const int key);
typedef void (*MapItemCallback)(int key, const MapTileDefinition* value);
void MapHashTableIterate(MapHashTable* map, MapItemCallback callback);
void RenderTilesFromHashTable(MapHashTable* map);
#endif