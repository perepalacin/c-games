#include "player.h"
#include "../main.h"
#include "../graphics/animation.h"

Texture2D atlas;
SpriteAnimation current_player_animation;
PlayerPos player_position;
bool is_player_moving = 0;
const int PLAYER_HEIGHT = 26;
static int player_direction = MALE_PLAYER_IDLE_DOWN;
static CharacterAnimationData player_animations[NUM_PLAYER_ACTIONS];

static Rectangle male_player_idle_up_frames[] = {
	// x, y, width, height
  	(Rectangle){10, 9, 20, 26},
};

static Rectangle male_player_walk_up_frames[] = {
    (Rectangle){10, 9, 20, 26},
	(Rectangle){42, 8, 20, 27},
	(Rectangle){10, 9, 20, 26},
	(Rectangle){74, 8, 20, 27}
};

static Rectangle male_player_run_up_frames[] = {
    (Rectangle){118, 8, 20, 26},
	(Rectangle){150, 6, 20, 29},
	(Rectangle){118, 8, 20, 26},
	(Rectangle){182, 6, 20, 29}
};

static Rectangle male_player_idle_right_frames[] = {
    (Rectangle){10, 105, 22, 26},
};

static Rectangle male_player_walk_right_frames[] = {
    (Rectangle){10, 105, 22, 26},
	(Rectangle){42, 104, 22, 27},
	(Rectangle){10, 105, 22, 26},
	(Rectangle){74, 104, 22, 27}
};

static Rectangle male_player_run_right_frames[] = {
    (Rectangle){121, 107, 22, 24},
	(Rectangle){152, 105, 23, 26},
	(Rectangle){121, 107, 22, 24},
	(Rectangle){185, 105, 22, 26}
};

static Rectangle male_player_idle_down_frames[] = {
    (Rectangle){9, 41, 22, 26},
};

static Rectangle male_player_walk_down_frames[] = {
    (Rectangle){9, 41, 22, 26},
	(Rectangle){41, 40, 22, 27},
	(Rectangle){9, 41, 22, 26},
	(Rectangle){73, 40, 22, 27}
};

static Rectangle male_player_run_down_frames[] = {
    (Rectangle){117, 40, 22, 24},
	(Rectangle){149, 42, 22, 25},
	(Rectangle){117, 40, 22, 24},
	(Rectangle){181, 42, 22, 25}
};

static Rectangle male_player_idle_left_frames[] = {
    (Rectangle){8, 73, 22, 26},
};

static Rectangle male_player_walk_left_frames[] = {
    (Rectangle){8, 73, 22, 26},
	(Rectangle){40, 72, 22, 27},
	(Rectangle){8, 73, 22, 26},
	(Rectangle){72, 72, 22, 27}
};

static Rectangle male_player_run_left_frames[] = {
    (Rectangle){113, 75, 22, 24},
	(Rectangle){145, 73, 23, 26},
	(Rectangle){113, 75, 22, 24},
	(Rectangle){177, 73, 22, 26}
};

void loadSprites (void) {
	player_animations[MALE_PLAYER_IDLE_UP] = (CharacterAnimationData){
        .frames = male_player_idle_up_frames,
        .frames_per_second = 1, 
        .frames_len = sizeof(male_player_idle_up_frames) / sizeof(male_player_idle_up_frames[0]),
    };

	player_animations[MALE_PLAYER_IDLE_RIGHT] = (CharacterAnimationData){
        .frames = male_player_idle_right_frames,
        .frames_per_second = 1, 
        .frames_len = sizeof(male_player_idle_right_frames) / sizeof(male_player_idle_right_frames[0]),
    };

	player_animations[MALE_PLAYER_IDLE_DOWN] = (CharacterAnimationData){
        .frames = male_player_idle_down_frames,
        .frames_per_second = 1, 
        .frames_len = sizeof(male_player_idle_down_frames) / sizeof(male_player_idle_down_frames[0]),
    };

	player_animations[MALE_PLAYER_IDLE_LEFT] = (CharacterAnimationData){
        .frames = male_player_idle_left_frames,
        .frames_per_second = 1, 
        .frames_len = sizeof(male_player_idle_left_frames) / sizeof(male_player_idle_left_frames[0]),
    };

    player_animations[MALE_PLAYER_WALK_UP] = (CharacterAnimationData){
        .frames = male_player_walk_up_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_walk_up_frames) / sizeof(male_player_walk_up_frames[0]),
    };

	player_animations[MALE_PLAYER_WALK_RIGHT] = (CharacterAnimationData){
        .frames = male_player_walk_right_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_walk_right_frames) / sizeof(male_player_walk_right_frames[0]),
    };

	player_animations[MALE_PLAYER_WALK_DOWN] = (CharacterAnimationData){
        .frames = male_player_walk_down_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_walk_up_frames) / sizeof(male_player_walk_up_frames[0]),
    };

	player_animations[MALE_PLAYER_WALK_LEFT] = (CharacterAnimationData){
        .frames = male_player_walk_left_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_walk_left_frames) / sizeof(male_player_walk_left_frames[0]),
    };

    player_animations[MALE_PLAYER_RUN_UP] = (CharacterAnimationData){
        .frames = male_player_run_up_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_run_up_frames) / sizeof(male_player_run_up_frames[0]),
    };

	player_animations[MALE_PLAYER_RUN_RIGHT] = (CharacterAnimationData){
        .frames = male_player_run_right_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_run_right_frames) / sizeof(male_player_run_right_frames[0]),
    };

	player_animations[MALE_PLAYER_RUN_DOWN] = (CharacterAnimationData){
        .frames = male_player_run_down_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_run_up_frames) / sizeof(male_player_run_up_frames[0]),
    };

	player_animations[MALE_PLAYER_RUN_LEFT] = (CharacterAnimationData){
        .frames = male_player_run_left_frames,
        .frames_per_second = 8,
        .frames_len = sizeof(male_player_run_left_frames) / sizeof(male_player_run_left_frames[0]),
    };
	for (int i = 12; i < NUM_PLAYER_ACTIONS; i++) {
		player_animations[i] = (CharacterAnimationData){
			.frames = male_player_walk_up_frames,
			.frames_per_second = 8,
			.frames_len = 4,
		};
	}

    player_position = (PlayerPos){ 0, 0};
}

void LoadPlayerTextures(void) {
    atlas = LoadTexture("./assets/sprites/player/players.png");
	loadSprites();
	CharacterAnimationData initial_data = player_animations[player_direction];
    current_player_animation = CreateSpriteAnimation(
        atlas,
        initial_data.frames_per_second,
        initial_data.frames,
        initial_data.frames_len
    );
}

int GetPlayerDirection () {
	return player_direction;
}

void SetPlayerDirection (const int new_direction) {
    if (player_direction != new_direction) {
        DisposeSpriteAnimation(current_player_animation);

        player_direction = new_direction;

        CharacterAnimationData new_anim_data = player_animations[player_direction];
        current_player_animation = CreateSpriteAnimation(
            atlas,
            new_anim_data.frames_per_second,
            new_anim_data.frames,
            new_anim_data.frames_len
        );
    }
}

void UpdatePlayerDirection (void) {
    is_player_moving = 1;
    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_W)) {
        SetPlayerDirection(MALE_PLAYER_RUN_UP);
        player_position.y -= 10;
    } else if (IsKeyDown(KEY_W)) {
        SetPlayerDirection(MALE_PLAYER_WALK_UP);
        player_position.y -= 5;
    } else if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_D)) {
        player_position.x += 10;
        SetPlayerDirection(MALE_PLAYER_RUN_RIGHT);
    } else if (IsKeyDown(KEY_D)) {
        SetPlayerDirection(MALE_PLAYER_WALK_RIGHT);
        player_position.x += 5;
    } else if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_S)) {
        player_position.y += 10;
        SetPlayerDirection(MALE_PLAYER_RUN_DOWN);
    } else if (IsKeyDown(KEY_S)) {
        player_position.y += 5;
        SetPlayerDirection(MALE_PLAYER_WALK_DOWN);
    } else if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_A)) {
        player_position.x -= 10;
        SetPlayerDirection(MALE_PLAYER_RUN_LEFT);
    } else if (IsKeyDown(KEY_A)) {
        player_position.x -= 5;
        SetPlayerDirection(MALE_PLAYER_WALK_LEFT);
    } else {
        is_player_moving = 0;
        if (player_direction == MALE_PLAYER_WALK_UP || player_direction == MALE_PLAYER_RUN_UP) SetPlayerDirection(MALE_PLAYER_IDLE_UP);
        else if (player_direction == MALE_PLAYER_WALK_RIGHT || player_direction == MALE_PLAYER_RUN_RIGHT) SetPlayerDirection(MALE_PLAYER_IDLE_RIGHT);
        else if (player_direction == MALE_PLAYER_WALK_DOWN || player_direction == MALE_PLAYER_RUN_DOWN) SetPlayerDirection(MALE_PLAYER_IDLE_DOWN);
        else if (player_direction == MALE_PLAYER_WALK_LEFT || player_direction == MALE_PLAYER_RUN_LEFT) SetPlayerDirection(MALE_PLAYER_IDLE_LEFT);
    }
}

void UpdatePlayerPosition(void) {
    if (GetPlayerDirection() == MALE_PLAYER_RUN_UP) {
        player_position.y -= 2;
    } else if (GetPlayerDirection() == MALE_PLAYER_WALK_UP) {
        player_position.y -= 1;
    } else if (GetPlayerDirection() == MALE_PLAYER_RUN_RIGHT) {
        player_position.x += 2;
    } else if (GetPlayerDirection() == MALE_PLAYER_WALK_RIGHT) {
        player_position.x += 1;
    } else if (GetPlayerDirection() == MALE_PLAYER_RUN_DOWN) {
        player_position.y += 2;
    } else if (GetPlayerDirection() == MALE_PLAYER_WALK_DOWN) {
        player_position.y += 1;
    } else if (GetPlayerDirection() == MALE_PLAYER_RUN_LEFT) {
        player_position.x -= 2;
    } else if (GetPlayerDirection() == MALE_PLAYER_WALK_LEFT) {
        player_position.x -= 1;
    } else {
        return;
    }
    
}

void UpdatePlayerState(void) { 
    if (is_player_moving) {
        UpdatePlayerPosition();
    } else {
        UpdatePlayerDirection();
    }
}

void DrawPlayer (void) {
	Rectangle dest = { player_position.x, player_position.y, GRID_SIZE, PLAYER_HEIGHT }; // Destination on the screen with respect to the origin of the sprite
	DrawSpriteAnimationPro(current_player_animation, dest, (Vector2) {0,PLAYER_HEIGHT}, 0, WHITE);
}
