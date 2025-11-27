#include "raylib.h"
#ifndef GAME_LOOP_H

#define MAX_POSSIBLE_MOVEMENTS 30

void initGame(void);
void mainGameLoop(void);
void selectNextPiece(void);
void selectPreviousPiece(void);
void selectPieceByCoordinates(Vector2);
#endif
