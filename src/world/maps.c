#include "maps.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

void LoadTileAssets(void) {
    tileset_atlas = LoadTexture("assets/tiles/my_tileset.png"); // Load your sprite sheet

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
}

void UnloadTileAssets(void) {
    UnloadTexture(tileset_atlas);
}