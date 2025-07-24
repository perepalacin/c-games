#include "maps.h"
#include "../entities/player.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

MapCell **game_map; 
const int MAP_WIDTH = 30;       
const int MAP_HEIGHT = 30;     
const int TILE_SIZE = 32;      

void LoadTileAssets(void) {
    tileset_atlas = LoadTexture("./assets/sprites/tiles/public_tiles1.png");
    if (tileset_atlas.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load ./assets/sprites/tiles/public_tiles1.png");
    }
    tile_definitions[GREEN_TREE_1] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){0, 19, 64, 45}, 
        .sprite_origin = (Vector2){16, 0},
    };
    
    tile_definitions[GREEN_TREE_2] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){64, 19, 64, 45}, 
        .sprite_origin = (Vector2){16, 0},
        .tile_width = 64,
        .tile_height = 45,
    };

    tile_definitions[GREEN_TREE_3] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){128, 19, 64, 45}, 
        .sprite_origin = (Vector2){16, 0},
        .tile_width = 64,
        .tile_height = 45,
    };

    tile_definitions[GREEN_TREE_4] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){192, 19, 64, 45}, 
        .sprite_origin = (Vector2){16, 0},
        .tile_width = 64,
        .tile_height = 45,
    };

    tile_definitions[GRASS_TILE_1] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){96, 2240, TILE_SIZE, TILE_SIZE}, 
        .sprite_origin = (Vector2){0, 0},
        .tile_width = TILE_SIZE,
        .tile_height = TILE_SIZE,
    };
}

void InitMap(void) {
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
            game_map[y][x].ground_layer = (MapTileDefinition){
                tile_definitions[GRASS_TILE_1].sprite_rectangle,
                tile_definitions[GRASS_TILE_1].sprite_origin,
                tile_definitions[GRASS_TILE_1].sprite_rectangle.width,
                tile_definitions[GRASS_TILE_1].sprite_rectangle.height,
                GRASS_TILE_1,
                1,
                EVENT_NONE
            };
            if (x % 2 == 0) {
                game_map[y][x].folliage_layer = (MapTileDefinition){
                    tile_definitions[GREEN_TREE_4].sprite_rectangle,
                    tile_definitions[GREEN_TREE_4].sprite_origin,
                    tile_definitions[GREEN_TREE_4].sprite_rectangle.width,
                    tile_definitions[GREEN_TREE_4].sprite_rectangle.height,
                    GREEN_TREE_4,
                    1,
                    EVENT_NONE
                };

            } else {
                game_map[y][x].folliage_layer = (MapTileDefinition){
                    tile_definitions[GREEN_TREE_2].sprite_rectangle,
                    tile_definitions[GREEN_TREE_2].sprite_origin,
                    tile_definitions[GREEN_TREE_2].sprite_rectangle.width,
                    tile_definitions[GREEN_TREE_2].sprite_rectangle.height,
                    GREEN_TREE_2,
                    1,
                    EVENT_NONE
                };
            }
        }
    }
}

void RenderMap(void) {
    bool is_player_drawn = 0;
    if (game_map == NULL) {
        TraceLog(LOG_WARNING, "Map not initialized. Cannot render.");
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileId = game_map[y][x].ground_layer.tile_id;
            if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
                MapTileDefinition def = tile_definitions[tileId];
                DrawTexturePro(tileset_atlas, def.sprite_rectangle, (Rectangle){x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE}, (Vector2)def.sprite_origin, 0.0f, WHITE);
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileId = game_map[y][x].folliage_layer.tile_id;
            if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
                MapTileDefinition def = tile_definitions[tileId];
                DrawTexturePro(tileset_atlas, def.sprite_rectangle, (Rectangle){x*TILE_SIZE, y*TILE_SIZE, def.tile_width, def.tile_height}, (Vector2)def.sprite_origin, 0.0f, WHITE);
            }
            // tileId = game_map[y][x].object_layer.tile_id;
            // if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
            //     MapTileDefinition def = tile_definitions[tileId];
                // DrawTexturePro(tileset_atlas, def.sprite_rectangle, (Rectangle){x*TILE_SIZE, y*TILE_SIZE, def.tile_width, def.tile_height}, (Vector2)def.sprite_origin, 0.0f, WHITE);
            // }
        }
        Vector2 player_pos = GetPlayerPosition();
        int player_y_pos = player_pos.y;
        if ((!is_player_drawn && player_y_pos == y) || player_y_pos < 0 || player_y_pos > MAP_HEIGHT) {
            DrawPlayer();
            is_player_drawn = 1;
        }
    }
}

void FreeMap(void) {
    if (game_map == NULL) {
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (game_map[y] != NULL) {
            free(game_map[y]);
            game_map[y] = NULL;
        }
    }

    free(game_map);
    game_map = NULL;
    printf("Map memory freed successfully.\n");
}


void UnloadTileAssets(void) {
    UnloadTexture(tileset_atlas);
}