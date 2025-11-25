#include "./board.h"
#include "../game-loop/game-loop.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Texture2D atlas;
bool isSpriteInitialized = false;
extern uint8_t selectedPiece;
extern PieceColor playerColor;

static const uint8_t boardSpriteXPadding = 16;
static const uint8_t boardSpriteYPadding = 8;

const Rectangle sprites[PIECE_TYPE_COUNT][2] = {
    {
        {96, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE PAWN
        {96, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK PAWN
    },
    {
        {80, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE KNIGHT
        {80, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK KNIGHT
    },
    {
        {64, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE BISHOP
        {64, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK BISHOP
    },
    {
        {48, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE ROOK
        {48, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK ROOK
    },
    {
        {32, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE QUEEN
        {32, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK QUEEN
    },
    {
        {16, 224, SQUARE_SIZE, SQUARE_SIZE}, // WHITE KING
        {16, 208, SQUARE_SIZE, SQUARE_SIZE}, // BLACK KING
    },
};

const Piece playerInitialPositions[TOTAL_PIECES_PER_TEAM] = {
    {COL_A, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_B, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_C, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_D, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_E, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_F, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_G, ROW_2, PIECE_PAWN, PLAYER_NONE, false},
    {COL_H, ROW_2, PIECE_PAWN, PLAYER_NONE, false},

    {COL_A, ROW_1, PIECE_ROOK, PLAYER_NONE, false},
    {COL_B, ROW_1, PIECE_KNIGHT, PLAYER_NONE, false},
    {COL_C, ROW_1, PIECE_BISHOP, PLAYER_NONE, false},
    {COL_D, ROW_1, PIECE_QUEEN, PLAYER_NONE, false},
    {COL_E, ROW_1, PIECE_KING, PLAYER_NONE, false},
    {COL_F, ROW_1, PIECE_BISHOP, PLAYER_NONE, false},
    {COL_G, ROW_1, PIECE_KNIGHT, PLAYER_NONE, false},
    {COL_H, ROW_1, PIECE_ROOK, PLAYER_NONE, false},
};

const Piece enemyInitialPositions[TOTAL_PIECES_PER_TEAM] = {
    {COL_A, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_B, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_C, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_D, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_E, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_F, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_G, ROW_7, PIECE_PAWN, PLAYER_NONE, false},
    {COL_H, ROW_7, PIECE_PAWN, PLAYER_NONE, false},

    {COL_A, ROW_8, PIECE_ROOK, PLAYER_NONE, false},
    {COL_B, ROW_8, PIECE_KNIGHT, PLAYER_NONE, false},
    {COL_C, ROW_8, PIECE_BISHOP, PLAYER_NONE, false},
    {COL_D, ROW_8, PIECE_QUEEN, PLAYER_NONE, false},
    {COL_E, ROW_8, PIECE_KING, PLAYER_NONE, false},
    {COL_F, ROW_8, PIECE_BISHOP, PLAYER_NONE, false},
    {COL_G, ROW_8, PIECE_KNIGHT, PLAYER_NONE, false},
    {COL_H, ROW_8, PIECE_ROOK, PLAYER_NONE, false}};

void loadSprites(void) {
    isSpriteInitialized = true;
    atlas = LoadTexture("sprites/atlas_white.png");
}

void unloadSprites(void) {
    isSpriteInitialized = false;
    UnloadTexture(atlas);
}

static uint8_t transformColsToPx(BOARD_COLS col) {
    return 16 + col * 16;
}

static uint8_t transformRowToPx(BOARD_ROWS row) {

    return 144 - (8 + (row + 1) * 16);
}

BOARD_COLS transformPxToCols(float px) {
    if (px < boardSpriteXPadding * SCALING_FACTOR ||
        px > SCREEN_WIDTH - (boardSpriteXPadding * SCALING_FACTOR)) {
        return COL_COUNT;
    }
    int col_index = ((px - SQUARE_SIZE * SCALING_FACTOR) / (SQUARE_SIZE * SCALING_FACTOR));
    if (col_index >= COL_A && col_index <= COL_H) {
        return (BOARD_COLS)col_index;
    }
    return COL_COUNT;
}

BOARD_ROWS transformPxToRows(float px) {
    if (px < boardSpriteYPadding * SCALING_FACTOR ||
        px > SCREEN_HEIGHT - (boardSpriteYPadding * SCALING_FACTOR)) {
        return ROW_COUNT;
    }

    int inverted_row_index =
        (px - (boardSpriteYPadding * SCALING_FACTOR)) / (SQUARE_SIZE * SCALING_FACTOR);

    if (inverted_row_index < ROW_1 || inverted_row_index >= ROW_COUNT) {
        return ROW_COUNT;
    }
    int row_index = ROW_COUNT - 1 - inverted_row_index;

    return (BOARD_ROWS)row_index;
}

static void renderPiece(BOARD_COLS col, BOARD_ROWS row, PieceType pieceType, PieceColor color) {
    Vector2 targetPosition = {transformColsToPx(col), transformRowToPx(row)};
    DrawTextureRec(atlas, sprites[pieceType][color], targetPosition, WHITE);
}

static void renderSelectionAura(BOARD_COLS col, BOARD_ROWS row) {
    Vector2 center = {transformColsToPx(col) + (double)SQUARE_SIZE / 2,
                      transformRowToPx(row) + (double)SQUARE_SIZE / 2};
    const uint8_t NUM_BLUR_PASSES = 10;
    for (int i = 0; i < NUM_BLUR_PASSES; i++) {

        float currentRadius = 0 + (float)(i * 1.25f);

        float alphaFactor = (float)(i + 1) / (float)NUM_BLUR_PASSES;
        Color auraColor = RED;
        auraColor.a = (unsigned char)(255 * alphaFactor * 0.25f);
        DrawCircleV(center, currentRadius, auraColor);
    }
}

void renderBoard(Piece *whitePiece, Piece *blackPiece) {
    if (!isSpriteInitialized) {
        exit(132);
    }
    Rectangle boardRectangle = {0, 0, 160, 144};
    DrawTextureRec(atlas, boardRectangle, (Vector2){0, 0}, WHITE);
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {

        if (!whitePiece->isTaken) {
            if (i == selectedPiece && playerColor == PLAYER_WHITE) {
                renderSelectionAura(whitePiece->colPosition, whitePiece->rowPosition);
            }
            renderPiece(whitePiece->colPosition, whitePiece->rowPosition, whitePiece->type,
                        whitePiece->color);
        }
        if (!blackPiece->isTaken) {
            if (i == selectedPiece && playerColor == PLAYER_BLACK) {
                renderSelectionAura(blackPiece->colPosition, blackPiece->rowPosition);
            }
            renderPiece(blackPiece->colPosition, blackPiece->rowPosition, blackPiece->type,
                        blackPiece->color);
        }
        whitePiece++;
        blackPiece++;
    }
}

void getPiecePossibleMovements(Piece *piece) {
    switch (piece->type) {
        case (PIECE_PAWN) {
        if (piece->color == PLAYER_WHITE) {

        }
        }
    }
}
