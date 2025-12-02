#include "./game-loop.h"
#include "../controls/controls.h"
#include "../game-history/game-history.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t selectedPiece = TOTAL_PIECES_PER_TEAM;

Piece whitePieces[TOTAL_PIECES_PER_TEAM];
Piece blackPieces[TOTAL_PIECES_PER_TEAM];

PieceColor playerColor = PLAYER_WHITE;
PieceColor playerTurn = PLAYER_WHITE;

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

static bool checkIfCellIsOccupied(PiecePosition *piecePosition);
static bool checkIfPieceCanBeTaken(PiecePosition *piecePosition);
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
    handlePieceMouseMovement();
}

static uint8_t getFirstNonTakenPiece(void) {
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (playerTurn == PLAYER_WHITE) {
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
        if (playerTurn == PLAYER_WHITE) {
            if (!whitePieces[i].isTaken) {
                return i;
            }
        }
        if (playerTurn == PLAYER_BLACK) {
            if (!blackPieces[i].isTaken) {
                return i;
            }
        }
    }
    return selectedPiece;
}

static uint8_t getPreviousAlivePiece(void) {
    for (int i = selectedPiece - 1; i >= 0; i--) {
        if (playerTurn == PLAYER_WHITE) {
            if (!whitePieces[i].isTaken) {
                return i;
            }
        }
        if (playerTurn == PLAYER_BLACK) {
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
        if (playerTurn == PLAYER_WHITE) {
            getPiecePossibleMovements(&whitePieces[selectedPiece]);
        } else {
            getPiecePossibleMovements(&blackPieces[selectedPiece]);
        }
        return;
    }
    selectedPiece = getNextAlivePiece();
    if (playerTurn == PLAYER_WHITE) {
        getPiecePossibleMovements(&whitePieces[selectedPiece]);
    } else {
        getPiecePossibleMovements(&blackPieces[selectedPiece]);
    }
}

void selectPreviousPiece(void) {
    selectedPiece = getPreviousAlivePiece();
    if (playerTurn == PLAYER_WHITE) {
        getPiecePossibleMovements(&whitePieces[selectedPiece]);
    } else {
        getPiecePossibleMovements(&blackPieces[selectedPiece]);
    }
}

void selectPieceByCoordinates(Vector2 coordinates) {
    const BOARD_COLS selectedCol = transformPxToCols(coordinates.x);
    const BOARD_ROWS selectedRow = transformPxToRows(coordinates.y);
    bool isSelectedPieceChanged = false;
    for (int i = 0; i < TOTAL_PIECES_PER_TEAM; i++) {
        if (i == selectedPiece) {
            continue;
        }
        if (playerTurn == PLAYER_WHITE) {
            if (whitePieces[i].isTaken) {
                continue;
                ;
            }
            if (whitePieces[i].piecePosition.colPosition == selectedCol &&
                selectedRow == whitePieces[i].piecePosition.rowPosition) {
                selectedPiece = i;
                isSelectedPieceChanged = true;
            }
        }
        if (playerTurn == PLAYER_BLACK) {
            if (blackPieces[i].isTaken) {
                continue;
                ;
            }
            if (blackPieces[i].piecePosition.colPosition == selectedCol &&
                selectedRow == blackPieces[i].piecePosition.rowPosition) {
                selectedPiece = i;
                isSelectedPieceChanged = true;
            }
        }
    }
    if (selectedPiece != TOTAL_PIECES_PER_TEAM && isSelectedPieceChanged) {
        if (playerTurn == PLAYER_WHITE) {
            getPiecePossibleMovements(&whitePieces[selectedPiece]);
        } else {
            getPiecePossibleMovements(&blackPieces[selectedPiece]);
        }
    }
}

static bool checkIfCellIsOccupied(PiecePosition *piecePosition) {
    return (board[piecePosition->colPosition][piecePosition->rowPosition] != NULL);
}

static bool checkIfPieceCanBeTaken(PiecePosition *piecePosition) {
    return (board[piecePosition->colPosition][piecePosition->rowPosition] != NULL &&
            board[piecePosition->colPosition][piecePosition->rowPosition]->color != playerTurn);
}

static bool isValidMovement(PiecePosition *targetPosition) {
    if ((int8_t)targetPosition->colPosition == COL_COUNT ||
        // TODO: replace this for an outofbounds method!
        (int8_t)targetPosition->colPosition < COL_A ||
        (int8_t)targetPosition->rowPosition == ROW_COUNT ||
        (int8_t)targetPosition->rowPosition < ROW_1) {
        return false;
    } else if (!checkIfCellIsOccupied(targetPosition) || checkIfPieceCanBeTaken(targetPosition)) {
        return true;
    }
    return false;
}

static void getBishopPossibleMoves(const PiecePosition *currentPiecePosition) {
    int8_t xDirection = 1;
    int8_t yDirection = 1;
    for (int direction = 0; direction < 4; direction++) {
        if (direction == 0) {
            xDirection = 1;
            yDirection = 1;
        } else if (direction == 1) {
            yDirection = -1;
        } else if (direction == 2) {
            xDirection = -1;
            yDirection = 1;
        } else {
            yDirection = -1;
        }
        for (int i = 1;; i++) {
            PiecePosition targetPosition =
                (PiecePosition){.colPosition = currentPiecePosition->colPosition + i * xDirection,
                                .rowPosition = currentPiecePosition->rowPosition + i * yDirection};
            if (isValidMovement(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
                if (checkIfPieceCanBeTaken(&targetPosition)) {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

static void getRookPossibleMoves(const PiecePosition *currentPiecePosition) {
    int8_t xDirection = 1;
    int8_t yDirection = 1;
    for (int direction = 0; direction < 4; direction++) {
        if (direction == 0) {
            xDirection = 1;
            yDirection = 0;
        } else if (direction == 1) {
            xDirection = -1;
        } else if (direction == 2) {
            xDirection = 0;
            yDirection = 1;
        } else {
            yDirection = -1;
        }
        for (int i = 1;; i++) {
            PiecePosition targetPosition =
                (PiecePosition){.colPosition = currentPiecePosition->colPosition + i * xDirection,
                                .rowPosition = currentPiecePosition->rowPosition + i * yDirection};
            if (isValidMovement(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
                if (checkIfPieceCanBeTaken(&targetPosition)) {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

void handleEndTurn(void) {
    if (playerTurn == PLAYER_WHITE) {
        playerTurn = PLAYER_BLACK;
    } else {
        playerTurn = PLAYER_WHITE;
    }
    selectedPiece = TOTAL_PIECES_PER_TEAM;
}

static void getPiecePossibleMovements(Piece *piece) {
    // TODO: add the check mechanics!
    piecePossibleMovementsCount = 0;
    int8_t movementDirection = -1;

    const PiecePosition currentPiecePosition = {.colPosition = piece->piecePosition.colPosition,
                                                .rowPosition = piece->piecePosition.rowPosition};
    PiecePosition targetPosition;
    switch (piece->type) {
    case (PIECE_PAWN): {
        if (piece->color == playerColor) {
            movementDirection = 1;
        } else {
            movementDirection = -1;
        }
        targetPosition = (PiecePosition){.colPosition = currentPiecePosition.colPosition,
                                         .rowPosition = currentPiecePosition.rowPosition +
                                                        (1 * movementDirection)};
        if (!checkIfCellIsOccupied(&targetPosition)) {
            piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
            piecePossibleMovementsCount++;
            if (currentPiecePosition.rowPosition == ROW_2 ||
                currentPiecePosition.rowPosition == ROW_7) {
                targetPosition = (PiecePosition){.colPosition = piece->piecePosition.colPosition,
                                                 .rowPosition = currentPiecePosition.rowPosition +
                                                                (2 * movementDirection)};
                if (!checkIfCellIsOccupied(&targetPosition)) {
                    piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                    piecePossibleMovementsCount++;
                }
            }
        }
        if (currentPiecePosition.colPosition != COL_H) {
            targetPosition = (PiecePosition){.colPosition = piece->piecePosition.colPosition + 1,
                                             .rowPosition = piece->piecePosition.rowPosition +
                                                            (1 * movementDirection)};
            if (checkIfPieceCanBeTaken(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
            }
        }
        if (currentPiecePosition.colPosition != COL_A) {
            targetPosition = (PiecePosition){.colPosition = piece->piecePosition.colPosition - 1,
                                             .rowPosition = piece->piecePosition.rowPosition +
                                                            (1 * movementDirection)};
            if (checkIfPieceCanBeTaken(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
            }
        }
        break;
    case PIECE_KNIGHT: {
        // Right knight for blacks crashes on click!
        // Only when player 1 is white.
        int8_t xDirection = 0;
        int8_t yDirection = 0;
        for (int direction = 0; direction < 4; direction++) {
            if (direction == 0) {
                xDirection = 1;
                yDirection = 1;
            } else if (direction == 1) {
                yDirection = -1;
            } else if (direction == 2) {
                xDirection = -1;
                yDirection = 1;
            } else {
                yDirection = -1;
            }
            targetPosition =
                (PiecePosition){.colPosition = currentPiecePosition.colPosition + (1 * xDirection),
                                .rowPosition = currentPiecePosition.rowPosition + (2 * yDirection)};
            if (isValidMovement(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
            }
            targetPosition =
                (PiecePosition){.colPosition = currentPiecePosition.colPosition + (2 * xDirection),
                                .rowPosition = currentPiecePosition.rowPosition + (1 * yDirection)};
            if (isValidMovement(&targetPosition)) {
                piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                piecePossibleMovementsCount++;
            }
        }
        break;
    }
    case PIECE_BISHOP: {
        getBishopPossibleMoves(&currentPiecePosition);
        break;
    }
    case PIECE_ROOK: {
        getRookPossibleMoves(&currentPiecePosition);
        break;
    }
    case PIECE_QUEEN:
        getBishopPossibleMoves(&currentPiecePosition);
        getRookPossibleMoves(&currentPiecePosition);
        break;
    case PIECE_KING: {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                targetPosition =
                    (PiecePosition){.colPosition = currentPiecePosition.colPosition + i,
                                    .rowPosition = currentPiecePosition.rowPosition + j};
                if (isValidMovement(&targetPosition)) {
                    piecePossibleMovements[piecePossibleMovementsCount] = targetPosition;
                    piecePossibleMovementsCount++;
                }
            }
        }
        break;
    }
    case PIECE_TYPE_COUNT:
        break;
    }
    }
}

void handleReleasePiece(Vector2 mousePosition) {
    const BOARD_COLS destinationCol = transformPxToCols(mousePosition.x);
    const BOARD_ROWS destinationRow = transformPxToRows(mousePosition.y);

    bool isValidMove = false;
    for (int i = 0; i < piecePossibleMovementsCount; i++) {
        if (piecePossibleMovements[i].colPosition == destinationCol &&
            piecePossibleMovements[i].rowPosition == destinationRow) {
            isValidMove = true;
        }
    }
    if (!isValidMove) {
        return;
    }
    if (checkIfPieceCanBeTaken(&(PiecePosition){destinationCol, destinationRow})) {
        Piece *pieceToDelete = board[destinationCol][destinationRow];
        pieceToDelete->isTaken = true;
        board[destinationCol][destinationRow] = NULL;
    }
    BOARD_COLS previousCol;
    BOARD_ROWS previousRow;
    Piece *piece;
    if (playerTurn == PLAYER_WHITE) {
        previousCol = whitePieces[selectedPiece].piecePosition.colPosition;
        previousRow = whitePieces[selectedPiece].piecePosition.rowPosition;
        piece = &whitePieces[selectedPiece];
        whitePieces[selectedPiece].piecePosition = (PiecePosition){destinationCol, destinationRow};
        board[previousCol][previousRow] = NULL;
        board[destinationCol][destinationRow] = &whitePieces[selectedPiece];
    } else {
        previousCol = blackPieces[selectedPiece].piecePosition.colPosition;
        previousRow = blackPieces[selectedPiece].piecePosition.rowPosition;
        blackPieces[selectedPiece].piecePosition = (PiecePosition){destinationCol, destinationRow};
        piece = &blackPieces[selectedPiece];
        board[previousCol][previousRow] = NULL;
        board[destinationCol][destinationRow] = &blackPieces[selectedPiece];
    }
    addMoveToHistory((PiecePosition){previousCol, previousRow},
                     (PiecePosition){
                         destinationCol,
                         destinationRow,
                     },
                     piece);
    handleEndTurn();
}
