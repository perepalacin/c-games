#include "maps.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

MapCell **game_map; 
const int MAP_WIDTH = 30;       
const int MAP_HEIGHT = 30;     
const int TILE_SIZE = 20;      

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
            } else {
                printf("Invalid tile ID encountered at (%d, %d): %d", x, y, tileId);
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileId = game_map[y][x].overhead_layer.tile_id;
            if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
                MapTileDefinition def = tile_definitions[tileId];
                DrawTextureRec(tileset_atlas, def.sprite_rectangle, (Vector2){x*def.tile_width, y*def.tile_height}, WHITE);
            } else {
                printf("Invalid tile ID encountered at (%d, %d): %d", x, y, tileId);
            }
        }
    }
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