package ui

import rl "github.com/gen2brain/raylib-go/raylib"

var enemyCircleXOffset = 768 + 65
var enemycircleYOffset = 8

var CombatBackgroundSprites = []MenuSprites{
	// Field Day
	{rl.Rectangle{X: 0, Y: 16, Width: 256, Height: 152},
		rl.Vector2{X: 0, Y: 0}},
}

var enemyCircleSprites = []MenuSprites{
	// Field Day
	{rl.Rectangle{X: CombatBackgroundSprites[0].spriteSelectionRectangle.X + float32(enemyCircleXOffset), Y: CombatBackgroundSprites[0].spriteSelectionRectangle.Y + float32(enemycircleYOffset), Width: 127, Height: 32},
		rl.Vector2{X: 128, Y: 72}},
}
