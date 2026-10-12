package core

var Pokedex = map[string]Pkmn{
	"pikachu": {
		pokedexIndex: 1,
		name:         "Pikachu",
		types:        []PkmnType{Electric},
		baseStats: PkmnStats{
			HP: 35, Attack: 55, Defense: 40, SpAttack: 50, SpDefense: 50, Speed: 90,
		},
	},
	"charizard": {
		pokedexIndex: 2,
		name:         "Charizard",
		types:        []PkmnType{Fire, Flying},
		baseStats: PkmnStats{
			HP: 78, Attack: 84, Defense: 78, SpAttack: 109, SpDefense: 85, Speed: 100,
		},
	},
	"blastoise": {
		pokedexIndex: 3,
		name:         "Blastoise",
		types:        []PkmnType{Water},
		baseStats: PkmnStats{
			HP: 79, Attack: 83, Defense: 100, SpAttack: 85, SpDefense: 105, Speed: 78,
		},
	},
	"venusaur": {
		pokedexIndex: 4,
		name:         "Venusaur",
		types:        []PkmnType{Grass, Poison},
		baseStats: PkmnStats{
			HP: 80, Attack: 82, Defense: 83, SpAttack: 100, SpDefense: 100, Speed: 80,
		},
	},
	"gengar": {
		pokedexIndex: 5,
		name:         "Gengar",
		types:        []PkmnType{Ghost, Poison},
		baseStats: PkmnStats{
			HP: 60, Attack: 65, Defense: 60, SpAttack: 130, SpDefense: 75, Speed: 110,
		},
	},
	"Pokedex": {
		pokedexIndex: 6,
		name:         "Snorlax",
		types:        []PkmnType{Normal},
		baseStats: PkmnStats{
			HP: 160, Attack: 110, Defense: 65, SpAttack: 65, SpDefense: 110, Speed: 30,
		},
	},
	"gyarados": {
		pokedexIndex: 7,
		name:         "Gyarados",
		types:        []PkmnType{Water, Flying},
		baseStats: PkmnStats{
			HP: 95, Attack: 125, Defense: 79, SpAttack: 60, SpDefense: 100, Speed: 81,
		},
	},
	"dragonite": {
		pokedexIndex: 8,
		name:         "Dragonite",
		types:        []PkmnType{Dragon, Flying},
		baseStats: PkmnStats{
			HP: 91, Attack: 134, Defense: 95, SpAttack: 100, SpDefense: 100, Speed: 80,
		},
	},
	"alakazam": {
		pokedexIndex: 9,
		name:         "Alakazam",
		types:        []PkmnType{Psychic},
		baseStats: PkmnStats{
			HP: 55, Attack: 50, Defense: 45, SpAttack: 135, SpDefense: 95, Speed: 120,
		},
	},
	"machamp": {
		pokedexIndex: 10,
		name:         "Machamp",
		types:        []PkmnType{Fighting},
		baseStats: PkmnStats{
			HP: 90, Attack: 130, Defense: 80, SpAttack: 65, SpDefense: 85, Speed: 55,
		},
	},
	"lapras": {
		pokedexIndex: 11,
		name:         "Lapras",
		types:        []PkmnType{Water, Ice},
		baseStats: PkmnStats{
			HP: 130, Attack: 85, Defense: 80, SpAttack: 85, SpDefense: 95, Speed: 60,
		},
	},
	"jolteon": {
		pokedexIndex: 12,
		name:         "Jolteon",
		types:        []PkmnType{Electric},
		baseStats: PkmnStats{
			HP: 65, Attack: 65, Defense: 60, SpAttack: 110, SpDefense: 95, Speed: 130,
		},
	},
}
