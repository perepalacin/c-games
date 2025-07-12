#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h" 

typedef enum {
    PLAYER_ANIM_IDLE_DOWN = 0,
    PLAYER_ANIM_IDLE_UP,
    PLAYER_ANIM_IDLE_LEFT,
    PLAYER_ANIM_IDLE_RIGHT,
    PLAYER_ANIM_WALK_DOWN,
    PLAYER_ANIM_WALK_UP,
    PLAYER_ANIM_WALK_LEFT,
    PLAYER_ANIM_WALK_RIGHT,
    NUM_PLAYER_ANIMATIONS
} PlayerAnimationState;

typedef struct {
    Vector2 logical_grid_pos;
    Vector2 pixel_pos;       
    PlayerAnimationState current_animation;
    int current_frame;
    double frame_timer;
    float animation_speed;
} Player;

void initPlayer(Player *player, Vector2 start_pos);
void updatePlayerAnimation(Player *player, float delta_time);
void drawPlayer(Player *player, Vector2 draw_position);
void loadPlayerSprites();
void unloadPlayerSprites();

#endif // PLAYER_H