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

extern PiecePosition piecePossibleMovements[MAX_POSSIBLE_MOVEMENTS];
extern uint8_t piecePossibleMovementsCount;

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

static void renderAura(PiecePosition cell, float radius, Color color) {
    Vector2 center = {transformColsToPx(cell.colPosition) + (double)SQUARE_SIZE / 2,
                      transformRowToPx(cell.rowPosition) + (double)SQUARE_SIZE / 2};
    const uint8_t NUM_BLUR_PASSES = 10;
    for (int i = 0; i < NUM_BLUR_PASSES; i++) {

        float currentRadius = 0 + (float)(i * radius / NUM_BLUR_PASSES);

        float alphaFactor = (float)(i + 1) / (float)NUM_BLUR_PASSES;
        color.a = (unsigned char)(255 * alphaFactor * 0.25f);
        DrawCircleV(center, currentRadius, color);
    }
}

static void renderPossibleMovements(void) {
    for (int i = 0; i < piecePossibleMovementsCount; i++) {
        renderAura(piecePossibleMovements[i], 5, YELLOW);
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
                renderAura((PiecePosition){whitePiece->piecePosition.colPosition,
                                           whitePiece->piecePosition.rowPosition},
                           10, RED);
                renderPossibleMovements();
            }
            renderPiece(whitePiece->piecePosition.colPosition,
                        whitePiece->piecePosition.rowPosition, whitePiece->type, whitePiece->color);
        }
        if (!blackPiece->isTaken) {
            if (i == selectedPiece && playerColor == PLAYER_BLACK) {
                renderAura((PiecePosition){blackPiece->piecePosition.colPosition,
                                           blackPiece->piecePosition.rowPosition},
                           10, RED);
                renderPossibleMovements();
            }
            renderPiece(blackPiece->piecePosition.colPosition,
                        blackPiece->piecePosition.rowPosition, blackPiece->type, blackPiece->color);
        }
        whitePiece++;
        blackPiece++;
    }
}
