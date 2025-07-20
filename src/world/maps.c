#include "maps.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

// The game map itself
MapCell **game_map; // A dynamically allocated 2D array of MapCell
const int MAP_WIDTH = 300;       // Total width of the map in tiles
const int MAP_HEIGHT = 300;     // Total height of the map in tiles
const int TILE_SIZE = 20;      // Pixel size of one tile (e.g., 32 for 32x32 pixels)

void LoadTileAssets(void) {
    tileset_atlas = LoadTexture("./assets/sprites/tiles/gen4_tileset.png");
    if (tileset_atlas.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load ./assets/sprites/tiles/gen4_tileset.png");
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
        // .sprite_rectangle = (Rectangle){96, 2240, 32, 32}, 
        .sprite_rectangle = (Rectangle){0, 0, 32, 32}, 
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
            game_map[y][x].overhead_layer = (Tile){-1, 1, EVENT_NONE};
            game_map[y][x].ground_layer.tile_id = GRASS_TILE_1;
            game_map[y][x].ground_layer.is_walkable = 1;
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

                Rectangle destRec = {(float)x * def.tile_width, (float)y * def.tile_height, (float)def.tile_width, (float)def.tile_height};

                DrawTextureRec(tileset_atlas, (Rectangle){0, 0, 32, 32}, (Vector2){x*32, y*32}, WHITE);
            } else {
                printf("Invalid tile ID encountered at (%d, %d): %d", x, y, tileId);
            }
        }
    }
    DrawTextureRec(tileset_atlas, (Rectangle){0, 0, 32, 32}, (Vector2){0, 0}, WHITE);
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