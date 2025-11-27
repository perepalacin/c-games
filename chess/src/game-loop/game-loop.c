#include "./game-loop.h"
#include "../board/board.h"
#include "../controls/controls.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t selectedPiece = TOTAL_PIECES_PER_TEAM;

Piece whitePieces[TOTAL_PIECES_PER_TEAM];
Piece blackPieces[TOTAL_PIECES_PER_TEAM];

PieceColor playerColor = PLAYER_WHITE;

Piece *board[COL_COUNT][ROW_COUNT];

PiecePosition piecePossibleMovements[MAX_POSSIBLE_MOVEMENTS];
uint8_t piecePossibleMovementsCount = 0;

const Piece playerInitialPositions[TOTAL_PIECES_PER_TEAM] = {
    {{COL_A, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_B, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_C, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_D, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_E, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_F, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_G, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_H, ROW_2}, PIECE_PAWN, PLAYER_NONE, false},

    {{COL_A, ROW_1}, PIECE_ROOK, PLAYER_NONE, false},
    {{COL_B, ROW_1}, PIECE_KNIGHT, PLAYER_NONE, false},
    {{COL_C, ROW_1}, PIECE_BISHOP, PLAYER_NONE, false},
    {{COL_D, ROW_1}, PIECE_QUEEN, PLAYER_NONE, false},
    {{COL_E, ROW_1}, PIECE_KING, PLAYER_NONE, false},
    {{COL_F, ROW_1}, PIECE_BISHOP, PLAYER_NONE, false},
    {{COL_G, ROW_1}, PIECE_KNIGHT, PLAYER_NONE, false},
    {{COL_H, ROW_1}, PIECE_ROOK, PLAYER_NONE, false},
};

const Piece enemyInitialPositions[TOTAL_PIECES_PER_TEAM] = {
    {{COL_A, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_B, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_C, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_D, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_E, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_F, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_G, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},
    {{COL_H, ROW_7}, PIECE_PAWN, PLAYER_NONE, false},

    {{COL_A, ROW_8}, PIECE_ROOK, PLAYER_NONE, false},
    {{COL_B, ROW_8}, PIECE_KNIGHT, PLAYER_NONE, false},
    {{COL_C, ROW_8}, PIECE_BISHOP, PLAYER_NONE, false},
    {{COL_D, ROW_8}, PIECE_QUEEN, PLAYER_NONE, false},
    {{COL_E, ROW_8}, PIECE_KING, PLAYER_NONE, false},
    {{COL_F, ROW_8}, PIECE_BISHOP, PLAYER_NONE, false},
    {{COL_G, ROW_8}, PIECE_KNIGHT, PLAYER_NONE, false},
    {{COL_H, ROW_8}, PIECE_ROOK, PLAYER_NONE, false}};

static bool checkIfCellIsOccupied(PiecePosition piecePosition);
static bool checkIfPieceCanBeTaken(PiecePosition piecePosition);
static void getPiecePossibleMovements(Piece *piece);

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
        board[whitePieces[i].piecePosition.colPosition][whitePieces[i].piecePosition.rowPosition] =
            &whitePieces[i];
        blackPieces[i].color = PLAYER_BLACK;
        board[blackPieces[i].piecePosition.colPosition][blackPieces[i].piecePosition.rowPosition] =
            &blackPieces[i];
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
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (playerColor == PLAYER_WHITE) {
            if (whitePieces[i].isTaken) {
                continue;
                ;
            }
            if (whitePieces[i].piecePosition.colPosition == selectedCol &&
                selectedRow == whitePieces[i].piecePosition.rowPosition) {
                selectedPiece = i;
            }
        }
        if (playerColor == PLAYER_BLACK) {
            if (blackPieces[i].isTaken) {
                continue;
                ;
            }
            if (blackPieces[i].piecePosition.colPosition == selectedCol &&
                selectedRow == blackPieces[i].piecePosition.rowPosition) {
                selectedPiece = i;
            }
        }
    }
    if (selectedPiece != TOTAL_PIECES_PER_TEAM) {
        if (playerColor == PLAYER_WHITE) {
            getPiecePossibleMovements(&whitePieces[selectedPiece]);
        } else {
            getPiecePossibleMovements(&blackPieces[selectedPiece]);
        }
    }
}

static bool checkIfCellIsOccupied(PiecePosition piecePosition) {
    return (board[piecePosition.colPosition][piecePosition.rowPosition] != NULL);
}

static bool checkIfPieceCanBeTaken(PiecePosition piecePosition) {
    return (board[piecePosition.colPosition][piecePosition.rowPosition] != NULL &&
            board[piecePosition.colPosition][piecePosition.rowPosition]->color != playerColor);
}

static void getPiecePossibleMovements(Piece *piece) {
    piecePossibleMovementsCount = 0;
    switch (piece->type) {
        int8_t movementDirection = -1;
    case (PIECE_PAWN):
        if (piece->color == playerColor) {
            movementDirection = 1;
            const PiecePosition currentPiecePosition = {
                .colPosition = piece->piecePosition.colPosition,
                .rowPosition = piece->piecePosition.rowPosition};

            PiecePosition targetPosition = {.colPosition = currentPiecePosition.colPosition,
                                            .rowPosition = currentPiecePosition.rowPosition +
                                                           (1 * movementDirection)};
            if (!checkIfCellIsOccupied(targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
                if (currentPiecePosition.rowPosition == ROW_2 ||
                    currentPiecePosition.rowPosition == ROW_7) {
                    targetPosition = (PiecePosition){
                        .colPosition = piece->piecePosition.colPosition,
                        .rowPosition = currentPiecePosition.rowPosition + (2 * movementDirection)};
                    if (!checkIfCellIsOccupied(targetPosition)) {
                        piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                        piecePossibleMovementsCount++;
                    }
                }
            }
            if (currentPiecePosition.colPosition != COL_H) {
                targetPosition = (PiecePosition){
                    .colPosition = piece->piecePosition.colPosition + 1,
                    .rowPosition = piece->piecePosition.rowPosition + (1 * movementDirection)};
                if (checkIfPieceCanBeTaken(targetPosition)) {
                    piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                    piecePossibleMovementsCount++;
                }
            } else if (currentPiecePosition.colPosition != COL_A) {
                targetPosition = (PiecePosition){
                    .colPosition = piece->piecePosition.colPosition - 1,
                    .rowPosition = piece->piecePosition.rowPosition + (1 * movementDirection)};
                if (checkIfPieceCanBeTaken(targetPosition)) {
                    piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                    piecePossibleMovementsCount++;
                }
            }
        case PIECE_KNIGHT:
            break;
        case PIECE_BISHOP:
            break;
        case PIECE_ROOK:
            break;
        case PIECE_QUEEN:
            break;
        case PIECE_KING:
            break;
        case PIECE_TYPE_COUNT:
            break;
        }
    }
}
