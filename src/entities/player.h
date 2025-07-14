#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum {
    MALE_PLAYER_IDLE, 
    MALE_PLAYER_WALK_UP,
    MALE_PLAYER_WALK_DOWN,
    MALE_PLAYER_WALK_LEFT,
    MALE_PLAYER_WALK_RIGHT,
    MALE_PLAYER_RUN_UP,
    MALE_PLAYER_RUN_DOWN,
    MALE_PLAYER_RUN_LEFT,
    MALE_PLAYER_RUN_RIGHT,
    MALE_PLAYER_CYCLE_UP,
    MALE_PLAYER_CYCLE_DOWN,
    MALE_PLAYER_CYCLE_LEFT,
    MALE_PLAYER_CYCLE_RIGHT,
    MALE_PLAYER_FISHING_UP,
    MALE_PLAYER_FISHING_DOWN,
    MALE_PLAYER_FISHING_LEFT,
    MALE_PLAYER_FISHING_RIGHT,
    // Female and more
    NUM_PLAYER_ACTIONS,
} PlayerAction;

typedef struct {
    Rectangle frames[5];
    int frames_per_second;
    int frames_count;
} PlayerAnimations;


void UpdateDrawFrame(void);
void LoadPlayerTextures(void);
void DrawPlayer(void);

#endif