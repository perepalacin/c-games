package core

import "os"

type Pkmn struct {
	pokedexIndex    uint16
	name            string
	types           []PkmnType
	baseStats       PkmnStats
	compatibleMoves []PkmnMove
}

type PkmnInCombat struct {
	pkmn         Pkmn
	status       PkmnStatus
	moves        []PkmnMove
	currentStats PkmnStats
	level        uint8
	gender       Gender
	nature       Nature
	accuracy     int
}

type Pokemon int

const (
	pikachu Pokemon = iota
	charizard
	blastoise
	venusaur
	gengar
	snorlax
	gyarados
	dragonite
	alakazam
	machamp
	lapras
	jolteon
)

var Pokedex = []Pkmn{
	{
		pokedexIndex: 1,
		name:         "Pikachu",
		types:        []PkmnType{Electric},
		baseStats: PkmnStats{
			HP: 35, Attack: 55, Defense: 40, SpAttack: 50, SpDefense: 50, Speed: 90,
		},
	},
	{
		pokedexIndex: 2,
		name:         "Charizard",
		types:        []PkmnType{Fire, Flying},
		baseStats: PkmnStats{
			HP: 78, Attack: 84, Defense: 78, SpAttack: 109, SpDefense: 85, Speed: 100,
		},
	},
	{
		pokedexIndex: 3,
		name:         "Blastoise",
		types:        []PkmnType{Water},
		baseStats: PkmnStats{
			HP: 79, Attack: 83, Defense: 100, SpAttack: 85, SpDefense: 105, Speed: 78,
		},
	},
	{
		pokedexIndex: 4,
		name:         "Venusaur",
		types:        []PkmnType{Grass, Poison},
		baseStats: PkmnStats{
			HP: 80, Attack: 82, Defense: 83, SpAttack: 100, SpDefense: 100, Speed: 80,
		},
	},
	{
		pokedexIndex: 5,
		name:         "Gengar",
		types:        []PkmnType{Ghost, Poison},
		baseStats: PkmnStats{
			HP: 60, Attack: 65, Defense: 60, SpAttack: 130, SpDefense: 75, Speed: 110,
		},
	},
	{
		pokedexIndex: 6,
		name:         "Snorlax",
		types:        []PkmnType{Normal},
		baseStats: PkmnStats{
			HP: 160, Attack: 110, Defense: 65, SpAttack: 65, SpDefense: 110, Speed: 30,
		},
	},
	{
		pokedexIndex: 7,
		name:         "Gyarados",
		types:        []PkmnType{Water, Flying},
		baseStats: PkmnStats{
			HP: 95, Attack: 125, Defense: 79, SpAttack: 60, SpDefense: 100, Speed: 81,
		},
	},
	{
		pokedexIndex: 8,
		name:         "Dragonite",
		types:        []PkmnType{Dragon, Flying},
		baseStats: PkmnStats{
			HP: 91, Attack: 134, Defense: 95, SpAttack: 100, SpDefense: 100, Speed: 80,
		},
	},
	{
		pokedexIndex: 9,
		name:         "Alakazam",
		types:        []PkmnType{Psychic},
		baseStats: PkmnStats{
			HP: 55, Attack: 50, Defense: 45, SpAttack: 135, SpDefense: 95, Speed: 120,
		},
	},
	{
		pokedexIndex: 10,
		name:         "Machamp",
		types:        []PkmnType{Fighting},
		baseStats: PkmnStats{
			HP: 90, Attack: 130, Defense: 80, SpAttack: 65, SpDefense: 85, Speed: 55,
		},
	},
	{
		pokedexIndex: 11,
		name:         "Lapras",
		types:        []PkmnType{Water, Ice},
		baseStats: PkmnStats{
			HP: 130, Attack: 85, Defense: 80, SpAttack: 85, SpDefense: 95, Speed: 60,
		},
	},
	{
		pokedexIndex: 12,
		name:         "Jolteon",
		types:        []PkmnType{Electric},
		baseStats: PkmnStats{
			HP: 65, Attack: 65, Defense: 60, SpAttack: 110, SpDefense: 95, Speed: 130,
		},
	},
}

func createPokemonInCombat(pokedexIndex int) PkmnInCombat {
	if pokedexIndex >= len(Pokedex) {
		os.Exit(1)
	}
	selectedPkmn := Pokedex[pokedexIndex]

	return PkmnInCombat{
		pkmn:         selectedPkmn,
		status:       Healthy,
		moves:        []PkmnMove{},
		currentStats: selectedPkmn.baseStats,
		level:        50,
		gender:       Female,
		nature:       Quiet,
		accuracy:     100,
	}
}
