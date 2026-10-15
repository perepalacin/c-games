package ui

import rl "github.com/gen2brain/raylib-go/raylib"

var menuTextures rl.Texture2D
var backgroundTextures rl.Texture2D

type menuPossibleState int

const (
	mainMenu menuPossibleState = iota
	combatMenu
)

type mainMenuAvailablePositions int

const (
	fight mainMenuAvailablePositions = iota
	bag
	run
	pkmn
)

var menuState = mainMenu
var mainMenuPosition = fight
var prevMainMenuPosition = fight

type MenuSprites struct {
	spriteSelectionRectangle rl.Rectangle
	screenPosition           rl.Vector2
}

var MenuBgSprites = map[string]MenuSprites{
	"MainMenu": {
		rl.Rectangle{X: 17, Y: 35, Width: 256, Height: 203},
		rl.Vector2{X: 0, Y: 198},
	},
	"CombatMenu": {
		rl.Rectangle{X: 17, Y: 248, Width: 256, Height: 203},
		rl.Vector2{X: 0, Y: 198},
	},
}

var MainMenuSelectionSprites = []MenuSprites{
	// Fight button
	{rl.Rectangle{X: 294, Y: 41, Width: 218, Height: 92},
		rl.Vector2{X: 19, Y: 36 + 198}},
	// Bag
	{rl.Rectangle{X: 294, Y: 202, Width: 80, Height: 46},
		rl.Vector2{X: 0, Y: 146 + 198}},
	// Run
	{rl.Rectangle{X: 294, Y: 202, Width: 80, Height: 46},
		rl.Vector2{X: 88, Y: 153 + 198}},
	// Pkmn
	{rl.Rectangle{X: 294, Y: 202, Width: 80, Height: 46},
		rl.Vector2{X: 176, Y: 146 + 198}},
}

func LoadMenuSprites() {
	menuTextures = rl.LoadTexture("../../images/combat-sprites.png")
	backgroundTextures = rl.LoadTexture("../../images/combat-bg.png")
}

func UnloadMenuSprites() {
	rl.UnloadTexture(menuTextures)
	rl.UnloadTexture(backgroundTextures)
}

func RenderUi() {
	switch menuState {
	case mainMenu:
		rl.DrawTextureRec(menuTextures, MenuBgSprites["MainMenu"].spriteSelectionRectangle, MenuBgSprites["MainMenu"].screenPosition, rl.White)
	case combatMenu:
		rl.DrawTextureRec(menuTextures, MenuBgSprites["CombatMenu"].spriteSelectionRectangle, MenuBgSprites["CombatMenu"].screenPosition, rl.White)
	}

	renderBackground()
	handleRenderMenuSelectors()
	handleMenuInput()
}

func handleMenuInput() {
	// TODO: add game state checks here!
	if menuState == mainMenu {
		handleMainMenuState()
	} else {
		handleCombatMenuState()
	}
}

func handleMainMenuState() {
	if mainMenuPosition == fight && rl.IsKeyPressed(rl.KeyEnter) {
		menuState = combatMenu
	} else if rl.IsKeyPressed(rl.KeyUp) && mainMenuPosition != fight {
		prevMainMenuPosition = mainMenuPosition
		mainMenuPosition = fight
	} else if rl.IsKeyPressed(rl.KeyDown) && mainMenuPosition == fight {
		if prevMainMenuPosition == 0 {
			mainMenuPosition = bag
		} else {
			mainMenuPosition = prevMainMenuPosition
		}
	} else if rl.IsKeyPressed(rl.KeyRight) && mainMenuPosition >= 1 && mainMenuPosition != 3 {
		mainMenuPosition += 1
	} else if rl.IsKeyPressed(rl.KeyLeft) && mainMenuPosition <= 3 && mainMenuPosition != 1 {
		mainMenuPosition -= 1
	}
}

func handleCombatMenuState() {
	if rl.IsKeyPressed(rl.KeyEscape) && menuState == combatMenu {
		menuState = mainMenu
	}
}

func handleRenderMenuSelectors() {
	if menuState == mainMenu {
		rl.DrawTextureRec(menuTextures, MainMenuSelectionSprites[mainMenuPosition].spriteSelectionRectangle, MainMenuSelectionSprites[mainMenuPosition].screenPosition, rl.White)
	}
}

func renderBackground() {
	rl.DrawTextureRec(backgroundTextures, CombatBackgroundSprites[0].spriteSelectionRectangle, CombatBackgroundSprites[0].screenPosition, rl.White)
	rl.DrawTextureRec(backgroundTextures, enemyCircleSprites[0].spriteSelectionRectangle, enemyCircleSprites[0].screenPosition, rl.White)
}
