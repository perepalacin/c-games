#include "./game-loop.h"
#include "../board/board.h"
#include "../controls/controls.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const Piece enemyInitialPositions[TOTAL_PIECES_PER_TEAM];
extern const Piece playerInitialPositions[TOTAL_PIECES_PER_TEAM];
uint8_t selectedPiece = TOTAL_PIECES_PER_TEAM;

Piece whitePieces[TOTAL_PIECES_PER_TEAM];
Piece blackPieces[TOTAL_PIECES_PER_TEAM];

PieceColor playerColor = PLAYER_BLACK;

void initGame(void) {
    if (playerColor == PLAYER_WHITE) {
        memcpy(whitePieces, playerInitialPositions, sizeof(Piece) * TOTAL_PIECES_PER_TEAM);
        memcpy(blackPieces, enemyInitialPositions, sizeof(Piece) * TOTAL_PIECES_PER_TEAM);
    } else {
        memcpy(whitePieces, enemyInitialPositions, sizeof(Piece) * TOTAL_PIECES_PER_TEAM);
        memcpy(blackPieces, playerInitialPositions, sizeof(Piece) * TOTAL_PIECES_PER_TEAM);
    }

    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        whitePieces[i].color = PLAYER_WHITE;
        blackPieces[i].color = PLAYER_BLACK;
    }
}

void mainGameLoop(void) {
    renderBoard(whitePieces, blackPieces);
    handleKeyboardNavigation();
    handleMouseNavigation();
}

static uint8_t getFirstNonTakenPiece(void) {
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (playerColor == PLAYER_WHITE) {
            if (!whitePieces[i].isTaken) {
                return i;
            }
        } else {
            if (!blackPieces[i].isTaken) {
                return i;
            }
        }
    }
    return -1;
}

static uint8_t getNextAlivePiece(void) {
    for (int i = selectedPiece + 1; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (playerColor == PLAYER_WHITE) {
            if (!whitePieces[i].isTaken) {
                return i;
            }
        }
        if (playerColor == PLAYER_BLACK) {
            if (!blackPieces[i].isTaken) {
                return i;
            }
        }
    }
    return selectedPiece;
}

static uint8_t getPreviousAlivePiece(void) {
    for (int i = selectedPiece - 1; i >= 0; i--) {
        if (playerColor == PLAYER_WHITE) {
            if (!whitePieces[i].isTaken) {
                return i;
            }
        }
        if (playerColor == PLAYER_BLACK) {
            if (!blackPieces[i].isTaken) {
                return i;
            }
        }
    }
    return selectedPiece;
}

void selectNextPiece(void) {
    if (selectedPiece == TOTAL_PIECES_PER_TEAM) {
        selectedPiece = getFirstNonTakenPiece();
        return;
    }
    selectedPiece = getNextAlivePiece();
}

void selectPreviousPiece(void) {
    selectedPiece = getPreviousAlivePiece();
}

void selectPieceByCoordinates(Vector2 coordinates) {
    const BOARD_COLS selectedCol = transformPxToCols(coordinates.x);
    const BOARD_ROWS selectedRow = transformPxToRows(coordinates.y);
    printf("Expected col %d, expected row %d\n", selectedCol, selectedRow);
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (playerColor == PLAYER_WHITE) {
            if (whitePieces[i].isTaken) {
                continue;
                ;
            }
            if (whitePieces[i].colPosition == selectedCol &&
                selectedRow == whitePieces[i].rowPosition) {
                selectedPiece = i;
            }
        }
        if (playerColor == PLAYER_BLACK) {
            if (blackPieces[i].isTaken) {
                continue;
                ;
            }
            if (blackPieces[i].colPosition == selectedCol &&
                selectedRow == blackPieces[i].rowPosition) {
                selectedPiece = i;
            }
        }
    }
}
