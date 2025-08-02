#include "maps.h"
#include "../entities/player.h"
#include "home_town.h"

Texture2D tileset_atlas;
MapTileDefinition tile_definitions[NUM_TILE_TYPES];

MapCell **game_map; 
const int  MAP_WIDTH = 30;       
const int MAP_HEIGHT = 30;     
const int TILE_SIZE = 32;      

void LoadMap(void) {
    game_map = InitMap();
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
        PlayerPos player_pos = GetPlayerGridPosition();
        if ((!is_player_drawn && player_pos.y >= y)) {
            DrawPlayer();
            is_player_drawn = 1;
            // TODO: Get user collisions!
        }
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileId = game_map[y][x].folliage_layer.tile_id;
            if (tileId >= 0 && tileId < NUM_TILE_TYPES) {
                MapTileDefinition def = tile_definitions[tileId];
                DrawTexturePro(tileset_atlas, def.sprite_rectangle, (Rectangle){x*TILE_SIZE, y*TILE_SIZE, def.tile_width, def.tile_height}, (Vector2)def.sprite_origin, 0.0f, WHITE);
            }
        }
    }
}

void UnloadMap (void) {
    FreeMap();
    UnloadTileAssets();
}