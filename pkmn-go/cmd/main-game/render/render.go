package render

import (
	"pkmn/internal/constants"
	"pkmn/menu"

	rl "github.com/gen2brain/raylib-go/raylib"
)


var camera2D rl.Camera2D = rl.Camera2D{
	Offset: rl.Vector2{X: 0, Y: 0},
	Target: rl.Vector2{X: 0, Y: 0},
	Rotation: 0,
	Zoom: 2,
}

func StartRendering () {
		rl.InitWindow(int32(constants.ScreenWidth), int32(constants.ScreenHeight), "Pokémon in Go")
		defer rl.CloseWindow()
		rl.SetExitKey(rl.KeyNull)
		rl.SetTargetFPS(60)
		menu.LoadMenuSprites()
		defer menu.UnloadMenuSprites()
		for !rl.WindowShouldClose() {
			rl.BeginDrawing()
			rl.BeginMode2D(camera2D)
			menu.RenderMenu()
			rl.EndMode2D()
			rl.EndDrawing()
	}
}