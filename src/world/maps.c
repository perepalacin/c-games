#include "maps.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

MapHashTable* myTileHashTable;
MapCell **game_map; 
const int MAP_WIDTH = 30;       
const int MAP_HEIGHT = 30;     
const int TILE_SIZE = 20;      
static MapItem HT_DELETED_ITEM = {0, NULL};

void LoadTileAssets(void) {
    // tileset_atlas = LoadTexture("./assets/sprites/tiles/gen4_tileset.png");
    tileset_atlas = LoadTexture("./assets/sprites/tiles/public_tiles1.png");
    if (tileset_atlas.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load ./assets/sprites/tiles/public_tiles1.png");
    }
    tile_definitions[GREEN_TREE_1] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){14, 19, 36, 45}, 
        .tile_width = 36,
        .tile_height = 45,
    };
    
    tile_definitions[GREEN_TREE_2] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){78, 19, 36, 45}, 
        .tile_width = 36,
        .tile_height = 45,
    };

    tile_definitions[GREEN_TREE_3] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){142, 19, 36, 45}, 
        .tile_width = 36,
        .tile_height = 45,
    };

    tile_definitions[GREEN_TREE_4] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){206, 19, 36, 45}, 
        .tile_width = 36,
        .tile_height = 45,
    };

    tile_definitions[GRASS_TILE_1] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){96, 2240, 32, 32}, 
        .tile_width = 32,
        .tile_height = 32,
    };
}

void InitMap (void) {
    game_map = (MapCell **)malloc(MAP_HEIGHT * sizeof(MapCell *));

    myTileHashTable = InitializeMapHashTable();
    if (myTileHashTable != NULL) {
        MapHashTableInsert(myTileHashTable, GenerateHashKey(0, 0), &tile_definitions[GREEN_TREE_1]);
        MapHashTableInsert(myTileHashTable, GenerateHashKey(0, 1), &tile_definitions[GREEN_TREE_2]);
        MapHashTableInsert(myTileHashTable, GenerateHashKey(0, 2), &tile_definitions[GREEN_TREE_3]);
        MapHashTableInsert(myTileHashTable, GenerateHashKey(0, 3), &tile_definitions[GREEN_TREE_4]);
    }
    
    if (game_map == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for map rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int y = 0;  y < MAP_HEIGHT; y++) {
        game_map[y] = (MapCell *)malloc(MAP_WIDTH*sizeof(MapCell));
        if (game_map[y] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory for map column %d. \n", y);
            for (int i = 0; i < y; i++) {
                free(game_map[i]);
            }
            free(game_map);
            exit(EXIT_FAILURE);
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game_map[y][x].ground_layer = (Tile){GRASS_TILE_1, 1, EVENT_NONE};
            game_map[y][x].object_layer = (Tile){-1, 1, EVENT_NONE};
            if (x % 2 == 0) {
                game_map[y][x].overhead_layer = (Tile){-1, 1, EVENT_NONE};
            } else {
                game_map[y][x].overhead_layer = (Tile){GREEN_TREE_1, 1, EVENT_NONE};
            }
        }
    }
}

void RenderMap(void) {
    if (game_map == NULL) {
        TraceLog(LOG_WARNING, "Map not initialized. Cannot render.");
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileId = game_map[y][x].ground_layer.tile_id;
            if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
                MapTileDefinition def = tile_definitions[tileId];
                DrawTextureRec(tileset_atlas, def.sprite_rectangle, (Vector2){x*def.tile_width, y*def.tile_height}, WHITE);
            }
        }
    }

    // for (int y = 0; y < MAP_HEIGHT; y++) {
    //     for (int x = 0; x < MAP_WIDTH; x++) {
    //         int tileId = game_map[y][x].overhead_layer.tile_id;
    //         if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
    //             MapTileDefinition def = tile_definitions[tileId];
    //             DrawTextureRec(tileset_atlas, def.sprite_rectangle, (Vector2){x*def.tile_width, y*def.tile_height}, WHITE);
    //         }
    //     }
    // }
    RenderTilesFromHashTable(myTileHashTable);
}


void FreeMap(void) {
    if (game_map == NULL) {
        return; // Nothing to free
    }

    // Free memory for each row
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (game_map[y] != NULL) {
            free(game_map[y]);
            game_map[y] = NULL; // Set to NULL after freeing
        }
    }

    // Free the array of row pointers
    free(game_map);
    game_map = NULL; // Set the main pointer to NULL after freeing
    printf("Map memory freed successfully.\n");
}


void UnloadTileAssets(void) {
    UnloadTexture(tileset_atlas);
}

static MapHashTable* InitializeMapHashTable() {
    MapHashTable* map = malloc(sizeof(MapHashTable));

    map->size = 53;
    map->count = 0;
    map->items = calloc((size_t)map->size, sizeof(MapItem*));
    return map;
}

unsigned int GenerateHashKey(int x_coord, int y_coord) {
    return (x_coord*1000 + y_coord);
}

static MapItem* AddMapItem(const int k, const MapTileDefinition* map_tile_def) {
    MapItem* i = malloc(sizeof(MapItem)); 
    if (i == NULL) {
        TraceLog(LOG_ERROR, "AddMapItem: Failed to allocate memory for MapItem.");
        return NULL; 
    }
    i->key =k;
    i->value = malloc(sizeof(MapTileDefinition));
    if (i->value == NULL) {
        TraceLog(LOG_ERROR, "AddMapItem: Failed to allocate memory for MapTileDefinition value.");
        free(i); 
        return NULL;
    }

    memcpy(i->value, map_tile_def, sizeof(MapTileDefinition));
    return i; 
}

static void DeleteMapItem(MapItem* i) {
    free(i->value);
    free(i);
}


void DeleteMapHashTable(MapHashTable* map_hash_table) {
    for (int i = 0; i < map_hash_table->size; i++) {
        MapItem* map_item = map_hash_table->items[i];
        if (map_item != NULL) {
            DeleteMapItem(map_item);
        }
    }
    free(map_hash_table->items);
    free(map_hash_table);
}

void MapHashTableInsert(MapHashTable* map, const int key, const MapTileDefinition* value) {
    MapItem* item = AddMapItem(key, value);
    map->items[key] = item;
    map->count++;
}

MapItem* MapHashTableSearch(MapHashTable* map, const int key) {
    MapItem* map_item = map->items[key];
    if (map_item) {
        return map_item;
    }
    return NULL;
}

void MapHashTableDelete(MapHashTable* map, const int key) {
    MapItem* map_item = map->items[key];
    if (map_item != NULL) {
        if (map_item != &HT_DELETED_ITEM) {
            DeleteMapItem(map_item);
            map->items[key] = &HT_DELETED_ITEM;
            map->count--;
        }
    }
}

void MapHashTableIterate(MapHashTable* map, MapItemCallback callback) {
    if (map == NULL || callback == NULL) {
        TraceLog(LOG_WARNING, "MapHashTableIterate: Map or callback is NULL. Cannot iterate.");
        return;
    }

    for (int i = 0; i < map->size; i++) {
        printf("rendering tile with index: %d\n", i);
        MapItem* item = map->items[i];
        printf("Checking to render: %d, %d \n", (item != NULL), (item != &HT_DELETED_ITEM));
        if (item != NULL && item != &HT_DELETED_ITEM) {
            printf("rendering tile on coordinates: %d, %d\n", item->value->tile_height, item->value->tile_width);
            callback(item->key, item->value);
        }
    }
}

static void RenderSingleTileFromHashTable(int key, const MapTileDefinition* value) {
    int x = key / 1000;
    int y = key % 1000;
    printf("coordinates - x: %d, y: %d. With sprite: %d", x, y, value->sprite_rectangle);
    DrawTextureRec(tileset_atlas, value->sprite_rectangle, (Vector2){(float)x * value->tile_width, (float)y * value->tile_height}, WHITE);
}

void RenderTilesFromHashTable(MapHashTable* map) {
    printf("Rendering map from hashtable!\n");
    if (map == NULL) {
        TraceLog(LOG_WARNING, "RenderTilesFromHashTable: Map is NULL. Cannot render.");
        return;
    }
    MapHashTableIterate(map, RenderSingleTileFromHashTable);
}
