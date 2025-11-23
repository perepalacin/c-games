#ifndef PKMN_H
#include "raylib.h"
#include <stdlib.h>

#define PKMN_NAME_MAX_LEN 24
#define PKMN_DESCRIPTION_MAX_LEN 40
#define PKMN_MAX_TYPES 2

typedef enum {
    NATURE_HARDY,   // +10% Attack / -10% Attack (Neutral)
    NATURE_LONELY,  // +10% Attack / -10% Defense
    NATURE_BRAVE,   // +10% Attack / -10% Speed
    NATURE_ADAMANT, // +10% Attack / -10% Sp. Attack
    NATURE_NAUGHTY, // +10% Attack / -10% Sp. Defense

    NATURE_BOLD,    // +10% Defense / -10% Attack
    NATURE_DOCILE,  // +10% Defense / -10% Defense (Neutral)
    NATURE_RELAXED, // +10% Defense / -10% Speed
    NATURE_IMPISH,  // +10% Defense / -10% Sp. Attack
    NATURE_LAX,     // +10% Defense / -10% Sp. Defense

    NATURE_TIMID,   // +10% Speed / -10% Attack
    NATURE_HASTY,   // +10% Speed / -10% Defense
    NATURE_SERIOUS, // +10% Speed / -10% Speed (Neutral)
    NATURE_JOLLY,   // +10% Speed / -10% Sp. Attack
    NATURE_NAIVE,   // +10% Speed / -10% Sp. Defense

    NATURE_MODEST,  // +10% Sp. Attack / -10% Attack
    NATURE_MILD,    // +10% Sp. Attack / -10% Defense
    NATURE_QUIET,   // +10% Sp. Attack / -10% Speed
    NATURE_BASHFUL, // +10% Sp. Attack / -10% Sp. Attack (Neutral)
    NATURE_RASH,    // +10% Sp. Attack / -10% Sp. Defense

    NATURE_CALM,    // +10% Sp. Defense / -10% Attack
    NATURE_GENTLE,  // +10% Sp. Defense / -10% Defense
    NATURE_SASSY,   // +10% Sp. Defense / -10% Speed
    NATURE_CAREFUL, // +10% Sp. Defense / -10% Sp. Attack
    NATURE_QUIRKY,  // +10% Sp. Defense / -10% Sp. Defense (Neutral)

    NATURE_COUNT
} PokemonNature;

typedef enum {
    PKMN_STATUS_NONE = 0, // No status condition is active

    PKMN_STATUS_SLEEP,     // SLP: Cannot move for 1-3 turns
    PKMN_STATUS_POISON,    // PSN: Takes damage every turn
    PKMN_STATUS_BURN,      // BRN: Takes damage every turn & lowers Attack
    PKMN_STATUS_FREEZE,    // FRZ: Cannot move (until thawed)
    PKMN_STATUS_PARALYSIS, // PAR: 25% chance to skip turn & lowers Speed

    // --- Volatile Status Conditions (In-Battle Only) ---
    PKMN_STATUS_CONFUSION,   // Confused: 33% chance to hit self
    PKMN_STATUS_FLINCH,      // Flinched: Misses the current turn (clears after turn)
    PKMN_STATUS_INFATUATION, // Infatuated: 50% chance to skip turn
    PKMN_STATUS_LEECH_SEED,  // Leech Seed: User recovers HP stolen from target
    PKMN_STATUS_TRAPPED,     // Trapped: Prevents switching out (e.g., Fire Spin, Mean Look)

    PKMN_STATE_FAINTED, // The Pokémon has 0 HP and is knocked out

    PKMN_STATUS_COUNT
} PokemonCombatStatus;

typedef struct {
    uint8_t hp;
    uint8_t attack;
    uint8_t defense;
    uint8_t sp_attack;
    uint8_t sp_defense;
    uint8_t speed;
} PkmnStats;

typedef enum {
    FEMALE,
    MALE,
    GENDER_COUNT,
} Gender;

typedef struct {
    Rectangle combatFront1;
    // Rectangle combatFront2;
    // Rectangle combatFrontShiny1;
    // Rectangle combatFrontShiny2;

    Rectangle combatBack1;
    // Rectangle combatBack2;
    // Rectangle combatBackShiny1;
    // Rectangle combatBackShiny2;

    Rectangle pcView1;
    Rectangle pcView2;

} PokemonSprites;

typedef enum {
    PKMN_TYPE_NONE,
    PKMN_TYPE_NORMAL,
    PKMN_TYPE_FIRE,
    PKMN_TYPE_WATER,
    PKMN_TYPE_GRASS,
    PKMN_TYPE_ELECTRIC,
    PKMN_TYPE_ICE,
    PKMN_TYPE_FIGHTING,
    PKMN_TYPE_POISON,
    PKMN_TYPE_GROUND,
    PKMN_TYPE_FLYING,
    PKMN_TYPE_PSYCHIC,
    PKMN_TYPE_BUG,
    PKMN_TYPE_ROCK,
    PKMN_TYPE_GHOST,
    PKMN_TYPE_DRAGON,
    PKMN_TYPE_STEEL,
    PKMN_TYPE_DARK,
    PKMN_TYPE_COUNT
} PokemonType;

typedef enum { PHYSICAL_MOVE_CATEGORY, SPECIAL_MOVE_CATEGORY, STATUS_MOVE_CATEGORY } MoveCategory;

typedef enum {
    MOVE_TACKLE = 0,
    MOVE_FLAMETHROWER,
    MOVE_SURF,
    MOVE_THUNDER_WAVE,
    MOVE_STONE_EDGE,
    MOVE_ROOST,
    MOVE_HYPER_BEAM,
    MOVE_FLY,
    MOVE_CLOSE_COMBAT,
    MOVE_AURA_SPHERE,
    MOVE_WILL_O_WISP,
    MOVE_ICE_BEAM,
    MOVE_ID_COUNT
} PkmnMoveID;

typedef struct {
    char name[PKMN_NAME_MAX_LEN + 1];
    PokemonType type;
    MoveCategory category;
    uint8_t power;
    uint8_t accuracy;
    uint8_t pp;
    uint8_t remainingPp;
    char description[PKMN_DESCRIPTION_MAX_LEN + 1];
    uint8_t effectChance;
    PokemonCombatStatus negativeEffect;
    bool requiresRest;
    bool requiresLoad;
} PkmnMove;

typedef struct PkmnLearningPath {
    PkmnMoveID move;
    uint8_t level;
    struct PkmnLearningPath *next;
} PkmnLearningPath;

typedef enum {
    PKMN_Turtwig = 0,
    PKMN_Grotle,
    PKMN_Torterra,
    PKMN_Chimchar,
    PKMN_Monferno,
    PKMN_Infernape,
    PKMN_Piplup,
    PKMN_Prinplup,
    PKMN_Empoleon,
    PKMN_Starly,
    PKMN_Staravia,
    PKMN_Staraptor,
    PKMN_Bidoof,
    PKMN_Bibarel,
    PKMN_Kricketot,
    PKMN_Kricketune,
    PKMN_Shinx,
    PKMN_Luxio,
    PKMN_Luxray,
    PKMN_Budew,
    PKMN_Roserade,
    PKMN_Cranidos,
    PKMN_Rampardos,
    PKMN_Shieldon,
    PKMN_Bastiodon,
    PKMN_Burmy,
    PKMN_Wormadam,
    PKMN_Mothim,
    PKMN_Combee,
    PKMN_Vespiquen,
    PKMN_Pachirisu,
    PKMN_Buizel,
    PKMN_Floatzel,
    PKMN_Cherubi,
    PKMN_Cherrim,
    PKMN_Shellos,
    PKMN_Gastrodon,
    PKMN_Aipom,
    PKMN_Ambipom,
    PKMN_Drifloon,
    PKMN_Drifblim,
    PKMN_Buneary,
    PKMN_Lopunny,
    PKMN_Mismagius,
    PKMN_Honchkrow,
    PKMN_Glameow,
    PKMN_Purugly,
    PKMN_Chingling,
    PKMN_Stunky,
    PKMN_Skuntank,
    PKMN_Bronzor,
    PKMN_Bronzong,
    PKMN_Bonsly,
    PKMN_Mime_Jr,
    PKMN_Happiny,
    PKMN_Chatot,
    PKMN_Spiritomb,
    PKMN_Gible,
    PKMN_Gabite,
    PKMN_Garchomp,
    PKMN_Munchlax,
    PKMN_Riolu,
    PKMN_Lucario,
    PKMN_Hippopotas,
    PKMN_Hippowdon,
    PKMN_Skorupi,
    PKMN_Drapion,
    PKMN_Croagunk,
    PKMN_Toxicroak,
    PKMN_Carnivine,
    PKMN_Finneon,
    PKMN_Lumineon,
    PKMN_Mantyke,
    PKMN_Snover,
    PKMN_Abomasnow,
    PKMN_Weavile,
    PKMN_Magnezone,
    PKMN_Lickilicky,
    PKMN_Rhyperior,
    PKMN_Tangrowth,
    PKMN_Electivire,
    PKMN_Magmortar,
    PKMN_Togekiss,
    PKMN_Yanmega,
    PKMN_Leafeon,
    PKMN_Glaceon,
    PKMN_Gliscor,
    PKMN_Mamoswine,
    PKMN_Porygon_Z,
    PKMN_Gallade,
    PKMN_Probopass,
    PKMN_Dusknoir,
    PKMN_Froslass,
    PKMN_Rotom,
    PKMN_Uxie,
    PKMN_Mesprit,
    PKMN_Azelf,
    PKMN_Dialga,
    PKMN_Palkia,
    PKMN_Heatran,
    PKMN_Regigigas,
    PKMN_Giratina,
    PKMN_Cresselia,
    PKMN_Phione,
    PKMN_Manaphy,
    PKMN_Darkrai,
    PKMN_Shaymin,
    PKMN_Arceus,
    PKMN_COUNT
} PokemonsEnum;

typedef struct {
    uint8_t level;
    PokemonsEnum nextPokemon;
} Evolution;

typedef struct Pokemon {
    PokemonsEnum pokedexId;
    char name[PKMN_NAME_MAX_LEN + 1];
    char givenName[PKMN_NAME_MAX_LEN + 1];
    Gender gender;
    uint32_t experince;
    uint8_t level;
    PokemonType types[PKMN_MAX_TYPES];
    PokemonNature nature;
    PkmnStats stats;
    uint8_t remainingHp;
    Evolution evolution;
    PkmnMoveID moves[4];
    PkmnLearningPath *learningPath;
    PokemonCombatStatus status;
    PokemonSprites sprites;
} Pokemon;
#endif
