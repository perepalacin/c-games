package core

type Gender int

const (
	Female Gender = iota
	male
)

type PkmnType int

const (
	normal PkmnType = iota
	Normal
	Fire
	Water
	Grass
	Electric
	Ice
	Fighting
	Poison
	Ground
	Flying
	Psychic
	Bug
	Rock
	Ghost
	Dragon
	Dark
	Steel
	Fairy
)

type Nature int

const (
	Hardy Nature = iota
	Lonely
	Brave
	Adamant
	Naughty
	Bold
	Docile
	Relaxed
	Impish
	Lax
	Timid
	Hasty
	Serious
	Jolly
	Naive
	Modest
	Mild
	Quiet
	Bashful
	Rash
	Calm
	Gentle
	Sassy
	Careful
	Quirky
)

type CategoryKey int

const (
	special CategoryKey = iota
	physical
	status
)

type PkmnStats struct {
	HP        uint8
	Attack    uint8
	Defense   uint8
	SpAttack  uint8
	SpDefense uint8
	Speed     uint8
}

type PkmnStatus int

const (
	Healthy PkmnStatus = iota
	Poisoned
	Burned
	Paralyzed
	Asleep
	Frozen
	Fainted
	Sleep
)

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

type TrainerClass int

const (
	AceTrainer TrainerClass = iota
	AromaLady
	Artist
	Beauty
	Biker
	BirdKeeper
	BlackBelt
	Bodybuilder
	BugCatcher
	Camper
	Collector
	Cyclist
	Doctor
	DoubleTeam
	DragonTamer
	Expert
	Fisherman
	GalacticGrunt
	Gentleman
	Guitarist
	Hiker
	Idol
	Interviewer
	Jogger
	Lass
	NinjaBoy
	Photographer
	Picnicker
	PokemonBreeder
	PokemonRanger
	PokemonTrainer
	PsychicTrainer
	Reporter
	RichBoy
	Roughneck
	RuinsManiac
	Sailor
	SchoolKid
	Scientist
	Skier
	Socialite
	Swimmer
	Tuber
	Veteran
	Worker
	Youngster
	GymLeader
	EliteFour
	Champion
	Rival
	GalacticLeader
	GalacticCommander
	InternationalPolice
	MagikarpSalesman
	Player
)

type Trainer struct {
	name     string
	variant  TrainerClass
	gender   Gender
	isPlayer bool
	pkmns    []PkmnInCombat
}

var Trainer1 = Trainer{
	name:     "Jose",
	variant:  Collector,
	gender:   male,
	isPlayer: false,
	pkmns:    []PkmnInCombat{},
}

var Player1 = Trainer{
	name:     "Max",
	variant:  Player,
	gender:   male,
	isPlayer: true,
	pkmns:    []PkmnInCombat{},
}
