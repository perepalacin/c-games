#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdio.h>

typedef enum {
    MALE_PLAYER_IDLE_UP, 
    MALE_PLAYER_IDLE_RIGHT, 
    MALE_PLAYER_IDLE_DOWN, 
    MALE_PLAYER_IDLE_LEFT, 
    MALE_PLAYER_WALK_UP,
    MALE_PLAYER_WALK_RIGHT,
    MALE_PLAYER_WALK_DOWN,
    MALE_PLAYER_WALK_LEFT,
    MALE_PLAYER_RUN_UP,
    MALE_PLAYER_RUN_RIGHT,
    MALE_PLAYER_RUN_DOWN,
    MALE_PLAYER_RUN_LEFT,
    MALE_PLAYER_CYCLE_UP,
    MALE_PLAYER_CYCLE_RIGHT,
    MALE_PLAYER_CYCLE_DOWN,
    MALE_PLAYER_CYCLE_LEFT,
    MALE_PLAYER_FISHING_UP,
    MALE_PLAYER_FISHING_RIGHT,
    MALE_PLAYER_FISHING_DOWN,
    MALE_PLAYER_FISHING_LEFT,
    // Female and more
    NUM_PLAYER_ACTIONS,
} PlayerAction;

typedef struct {
    int x;
    int y;
} PlayerPos;

typedef struct {
    Rectangle *frames;
    int frames_len;        
    int frames_per_second;
} CharacterAnimationData;


void LoadPlayerTextures(void);
void DrawPlayer(void);
void UpdatePlayerState(void);
Vector2 GetPlayerPosition();
PlayerPos GetPlayerGridPosition();
void SetPlayerGridPosition(PlayerPos);

#endif