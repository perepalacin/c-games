#ifndef BOARD_H
#include "raylib.h"
#include <stdlib.h>

#define TOTAL_PIECES_PER_TEAM 16
#define SQUARE_SIZE 16

typedef enum {
    PLAYER_WHITE = 0,
    PLAYER_BLACK,
    PLAYER_NONE, // invalid state used for initializing pieces without a team.
} PieceColor;

typedef enum { COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G, COL_H, COL_COUNT } BOARD_COLS;

typedef enum { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_COUNT } BOARD_ROWS;

typedef enum {
    PIECE_PAWN = 0,
    PIECE_KNIGHT,
    PIECE_BISHOP,
    PIECE_ROOK,
    PIECE_QUEEN,
    PIECE_KING,
    PIECE_TYPE_COUNT
} PieceType;

typedef struct {
    BOARD_COLS colPosition;
    BOARD_ROWS rowPosition;
    PieceType type;
    PieceColor color;
    bool isTaken;
} Piece;

void loadSprites(void);
void unloadSprites(void);
void renderBoard(Piece *whitePiece, Piece *blackPiece);
BOARD_COLS transformPxToCols(float px);
BOARD_ROWS transformPxToRows(float px);

#endif
