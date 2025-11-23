#include "./combat.h"
#include "../menus/menus.h"
#include "../pkmn/pkmn.h"
#include "raylib.h"

Texture2D pkmnFrontSprites;
Texture2D pkmnBackSprites;
Texture2D trainerSprites;
Texture2D playerSprites;
bool initializedCombatSprites = false;

void loadCombatTextures(void) {
    pkmnFrontSprites = LoadTexture("images/sprites/pkmns-front.png");
    pkmnBackSprites = LoadTexture("images/sprites/pkmns-back.png");
    trainerSprites = LoadTexture("images/sprites/trainsers-front.png");
    playerSprites = LoadTexture("images/sprites/trainsers-back.png");
    initializedCombatSprites = true;
}

Pokemon enemyPkmn = {
    .pokedexId = PKMN_Turtwig,
    .name = "Turtwig",
    .gender = MALE,
    .experince = 0,
    .level = 1,
    .types =
        {
            PKMN_TYPE_ELECTRIC,
            PKMN_TYPE_NONE,
        },
    .nature = NATURE_DOCILE,
    .stats =
        {.hp = 55, .attack = 68, .defense = 64, .sp_attack = 45, .sp_defense = 55, .speed = 31},
    .remainingHp = 202,
    .moves = {MOVE_TACKLE, MOVE_THUNDER_WAVE, MOVE_CLOSE_COMBAT},
    .learningPath = NULL,
    .status = PKMN_STATUS_NONE,
    .sprites = {.combatFront1 = {0, 0, 96, 96},
                .combatBack1 = {0, 0, 96, 96},
                .pcView1 = {0, 0, 0, 0},
                .pcView2 = {0, 0, 0, 0}},
    .evolution = {.level = 18, .nextPokemon = PKMN_Grotle}};

Pokemon playerPkmn = {
    .pokedexId = PKMN_Grotle,
    .name = "Grotle",
    .gender = FEMALE,
    .experince = 0,
    .level = 1,
    .types =
        {
            PKMN_TYPE_GRASS,
            PKMN_TYPE_GROUND,
        },
    .nature = NATURE_DOCILE,
    .stats =
        {.hp = 75, .attack = 89, .defense = 85, .sp_attack = 55, .sp_defense = 65, .speed = 36},
    .remainingHp = 202,
    .moves = {MOVE_TACKLE, MOVE_AURA_SPHERE, MOVE_CLOSE_COMBAT},
    .learningPath = NULL,
    .status = PKMN_STATUS_NONE,
    .sprites = {.combatFront1 = {96, 0, 96, 96},
                .combatBack1 = {96, 0, 96, 96},
                .pcView1 = {0, 0, 0, 0},
                .pcView2 = {0, 0, 0, 0}},
    .evolution = {.level = 32, .nextPokemon = PKMN_Torterra}};

void unloadCombatTextures(void) {
    UnloadTexture(pkmnFrontSprites);
    UnloadTexture(pkmnBackSprites);
    UnloadTexture(trainerSprites);
    UnloadTexture(playerSprites);
    initializedCombatSprites = false;
}

static void renderEnemy(void) {
    Vector2 enemyTargetPosition = {140, 25};
    DrawTextureRec(pkmnFrontSprites, enemyPkmn.sprites.combatFront1, enemyTargetPosition, WHITE);
}

static void renderPlayer(void) {
    Vector2 playerTargetPosition = {.0f, 90};
    DrawTextureRec(pkmnBackSprites, playerPkmn.sprites.combatBack1, playerTargetPosition, WHITE);
}

void renderCombat(void) {
    if (!initializedCombatSprites) {
        exit(132);
    }
    renderEnemy();
    renderPlayer();
    renderMainCombatMenu();
}
