#include "player.h"
#include "../main.h"
#include "../graphics/animation.h"

Texture2D atlas;
SpriteAnimation animation;
const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 26;

void LoadPlayerTextures(void) {
    atlas = LoadTexture("./assets/sprites/player/players.png");
	animation = CreateSpriteAnimation(atlas, 8, (Rectangle[]) {
		(Rectangle){10, 9, 20, 26},
		(Rectangle){42, 8, 20, 27},
		(Rectangle){10, 9, 20, 26},
		(Rectangle){74, 8, 20, 27}
	}, 4);
}

void DrawPlayer (void) {
	Vector2 origin = { (PLAYER_WIDTH / 2), (PLAYER_HEIGHT / 2) }; // origin with respect to the sprite!
	Rectangle dest = { (SCREEN_WIDTH / 2) - (PLAYER_WIDTH / 2), (SCREEN_HEIGHT / 2) - (PLAYER_HEIGHT / 2), PLAYER_WIDTH * 2, PLAYER_HEIGHT * 2 }; // Destination on the screen with respect to the origin of the sprite
	// Rectangle dest = { (SCREEN_WIDTH / 2) - (PLAYER_WIDTH / 2), (SCREEN_HEIGHT / 2) - (PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT };
	DrawSpriteAnimationPro(animation, dest, origin, 0, WHITE);
}

static const Rectangle male_player_idle_frames[] = {
    (Rectangle){10, 9, 20, 26},
    (Rectangle){42, 8, 20, 27},
    (Rectangle){74, 8, 20, 27}
};

static const Rectangle male_player_walk_up_frames[] = {
    (Rectangle){10, 9, 20, 26},
	(Rectangle){42, 8, 20, 27},
	(Rectangle){10, 9, 20, 26},
	(Rectangle){74, 8, 20, 27}
};

// Animation player_animations[NUM_PLAYER_ACTIONS] = {
//     [MALE_PLAYER_IDLE] = {
//         .frames = (Rectangle*)male_player_idle_frames,
//         .frames_count = sizeof(male_player_idle_frames) / sizeof(male_player_idle_frames[0]),
//         .frames_per_second = 3,
//     },
//     [MALE_PLAYER_WALK_UP] = {
//         .frames = (Rectangle*)male_player_walk_up_frames,
//         .frames_count = sizeof(male_player_walk_up_frames) / sizeof(male_player_walk_up_frames[0]),
//         .frames_per_second = 3,
//     },
// };

// void create_player_sprite (void) {
//     animation = create_sprite_animation(atlas, player_animations[MALE_PLAYER_WALK_UP].frames_per_second, player_animations[MALE_PLAYER_WALK_UP].frames, player_animations[MALE_PLAYER_WALK_UP].frames_count);
// }

// void update_player_sprite(void) {
// 	Rectangle dest = { SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT / 2 - PLAYER_HEIGHT / 2, 40, 52 };
// 	Vector2 origin = { 0 };
//     draw_sprite_animation_pro(animation, dest, origin, 0, WHITE);
// }