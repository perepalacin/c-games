#include "maps.h"
#include "home_town.h"

MapCell **game_map;
Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];
extern int MAP_HEIGHT;
extern int MAP_WIDTH;
extern int TILE_SIZE;

void LoadTileAssets(void) {
    tileset_atlas = LoadTexture("./assets/sprites/tiles/public_tiles1.png");
    if (tileset_atlas.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load ./assets/sprites/tiles/public_tiles1.png");
    }
    tile_definitions[GREEN_TREE_1] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){0, 19, 64, 45}, 
        .sprite_origin = (Vector2){16, 0},
        .tile_width = 64,
        .tile_height = 45,
    };
    
    tile_definitions[GREEN_TREE_2] = (MapTileDefinition){
        .sprite_rectangle = (Rectangle){64, 19, 64, 45}, 
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

MapCell **InitMap(void) {
    LoadTileAssets();

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
            // if (x == 0 || x == (MAP_WIDTH -1)) {
            //     if (y % 2 == 0) {
            //         game_map[y][x].folliage_layer = (MapTileDefinition){
            //             tile_definitions[GREEN_TREE_2].sprite_rectangle,
            //             tile_definitions[GREEN_TREE_2].sprite_origin,
            //             tile_definitions[GREEN_TREE_2].sprite_rectangle.width,
            //             tile_definitions[GREEN_TREE_2].sprite_rectangle.height,
            //             GREEN_TREE_2,
            //             1,
            //             EVENT_NONE
            //         };
            //     } else {
            //         game_map[y][x].folliage_layer = (MapTileDefinition){
            //             tile_definitions[GREEN_TREE_1].sprite_rectangle,
            //             tile_definitions[GREEN_TREE_1].sprite_origin,
            //             tile_definitions[GREEN_TREE_1].sprite_rectangle.width,
            //             tile_definitions[GREEN_TREE_1].sprite_rectangle.height,
            //             GREEN_TREE_1,
            //             1,
            //             EVENT_NONE
            //         };
            //     }
            // }
            if (y == 0 || (y == (MAP_HEIGHT - 1))) {
                if (x % 2 == 0) {
                    printf("Draw tree 1 at -> x: %d, y: %d \n", x, y);
                    game_map[y][x].folliage_layer = (MapTileDefinition){
                        tile_definitions[GREEN_TREE_1].sprite_rectangle,
                        tile_definitions[GREEN_TREE_1].sprite_origin,
                        tile_definitions[GREEN_TREE_1].sprite_rectangle.width,
                        tile_definitions[GREEN_TREE_1].sprite_rectangle.height,
                        GREEN_TREE_1,
                        1,
                        EVENT_NONE
                    };
                } else {
                    printf("Draw tree 2 at -> x: %d, y: %d \n", x, y);
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
    return game_map;
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