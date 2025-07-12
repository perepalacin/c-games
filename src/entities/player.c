#include "player.h"

typedef struct {
    Texture2D texture;
    Vector2 frame_size;      
    int num_frames_per_row;  
} PlayerSpriteSheet;

int player_direction = 0;

PlayerSpriteSheet player_sprite_sheet;

int animation_start_frame[] = {
    0,
    1,
    2,
    3,
    4,
    8,
    12, 
    16  
};
int animation_num_frames[] = {
    1, 
    1, 
    1, 
    1, 
    4, 
    4, 
    4, 
    4  
};


void initPlayer(Player *player, Vector2 start_grid_pos) {
    player->logical_grid_pos = start_grid_pos;
    player->pixel_pos = (Vector2){start_grid_pos.x * 32.0f, start_grid_pos.y * 32.0f};
    player->current_animation = PLAYER_ANIM_IDLE_DOWN;
    player->current_frame = animation_start_frame[PLAYER_ANIM_IDLE_DOWN];
    player->frame_timer = 0.0;
    player->animation_speed = 5.0f;
}


void loadPlayerSprites() {
    player_sprite_sheet.texture = LoadTexture("assets/sprites/player_sprites.png");
    player_sprite_sheet.frame_size = (Vector2){32, 32};
    player_sprite_sheet.num_frames_per_row = player_sprite_sheet.texture.width / (int)player_sprite_sheet.frame_size.x;
}

void unloadPlayerSprites() {
    UnloadTexture(player_sprite_sheet.texture);
}

void setPlayerDirection () {
    if (IsKeyDown(KEY_UP)) {
        player_direction = 0;
    } else if (IsKeyDown(KEY_RIGHT)) {
        player_direction = 90;
    } else if (IsKeyDown(KEY_DOWN)) {
        player_direction = 180;
    } else if (IsKeyDown(KEY_LEFT)) {
        player_direction = 270;
    }
}

void updatePlayerAnimation(Player *player, float delta_time) {
    if (player->current_animation < 0 || player->current_animation >= NUM_PLAYER_ANIMATIONS) {
        return; 
    }

    int start_frame = animation_start_frame[player->current_animation];
    int num_frames = animation_num_frames[player->current_animation];

    if (num_frames <= 1) {
        player->current_frame = start_frame;
        player->frame_timer = 0.0;
        return;
    }

    player->frame_timer += delta_time; 

    float frame_duration = 1.0f / player->animation_speed;

    if (player->frame_timer >= frame_duration) {
        player->current_frame = (player->current_frame + 1);
        if (player->current_frame >= (start_frame + num_frames)) {
            player->current_frame = start_frame; 
        }
        player->frame_timer -= frame_duration; 
    }
}

void drawPlayer(Player *player, Vector2 draw_position) {
    Rectangle source_rect;
    source_rect.x = (float)(player->current_frame % player_sprite_sheet.num_frames_per_row) * player_sprite_sheet.frame_size.x;
    source_rect.y = (float)(player->current_frame / player_sprite_sheet.num_frames_per_row) * player_sprite_sheet.frame_size.y;
    source_rect.width = player_sprite_sheet.frame_size.x;
    source_rect.height = player_sprite_sheet.frame_size.y;

    Rectangle dest_rect;
    dest_rect.x = draw_position.x;
    dest_rect.y = draw_position.y;
    dest_rect.width = player_sprite_sheet.frame_size.x;
    dest_rect.height = player_sprite_sheet.frame_size.y;

    DrawTextureRec(player_sprite_sheet.texture, source_rect, draw_position, WHITE);
}

// In your main game loop (inside game_render() in main.c)
// Assuming g_player.pixel_x, g_player.pixel_y hold the player's current pixel position
// drawPlayer(&g_player, (Vector2){g_player.pixel_x, g_player.pixel_y});

// In your main game loop (inside game_update() or player_update() in main.c)
// Assuming you have a Player struct instance named 'g_player'
// Calculate delta_time (time since last frame)
// float delta_time = GetFrameTime(); // Raylib provides this!
// updatePlayerAnimation(&g_player, delta_time);

// And when player state changes (e.g., from IDLE to WALK_DOWN):
// g_player.current_animation = PLAYER_ANIM_WALK_DOWN;
// g_player.current_frame = animation_start_frame[PLAYER_ANIM_WALK_DOWN]; // Reset frame
// g_player.frame_timer = 0.0; // Reset timer
// g_player.animation_speed = 8.0f; // Example: 8 frames per second for walking