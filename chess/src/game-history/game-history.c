#include "./game-history.h"
#include "../game-loop/game-loop.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Move {
    PiecePosition initialPosition;
    PiecePosition finalPosition;
    Piece *piece;
    struct Move *next;
    struct Move *prev;
} Move;

int debuggingNode = 0;
Move *history_head = NULL;
Move *history_tail = NULL;
extern Piece *board[COL_COUNT][ROW_COUNT];

void addMoveToHistory(PiecePosition initialPosition, PiecePosition finalPosition, Piece *piece) {
    Move *newMove = (Move *)malloc(sizeof(Move));
    if (newMove == NULL) {
        fprintf(stderr, "Fatal: Memory allocation failed in addMoveToHistory.\n");
        exit(1);
    }
    newMove->initialPosition = initialPosition;
    newMove->finalPosition = finalPosition;
    newMove->piece = piece;
    newMove->next = NULL;
    newMove->prev = NULL;
    if (history_head == NULL) {
        history_head = newMove;
        history_tail = newMove;
    } else {
        history_tail->next = newMove;
        newMove->prev = history_tail;
        history_tail = newMove;
    }
}

void revertMove(void) {
    const Move *moveToRevert = history_tail;
    if (moveToRevert == NULL) {
        return;
    }

    // What if a piece was taken here?
    moveToRevert->piece->piecePosition = moveToRevert->initialPosition;
    board[moveToRevert->finalPosition.colPosition][moveToRevert->finalPosition.rowPosition] = NULL;
    board[moveToRevert->initialPosition.colPosition][moveToRevert->initialPosition.rowPosition] =
        moveToRevert->piece;
    if (history_tail->prev != NULL) {
        history_tail = history_tail->prev;
    }
    handleEndTurn();
}

void forwardMove(void) {
    if (history_tail == NULL) {
        return;
    }
    Move *moveNodeToExecute = history_tail;
    // What if a piece was taken here?
    moveNodeToExecute->piece->piecePosition = moveNodeToExecute->finalPosition;
    board[moveNodeToExecute->initialPosition.colPosition]
         [moveNodeToExecute->initialPosition.rowPosition] = NULL;
    board[moveNodeToExecute->finalPosition.colPosition]
         [moveNodeToExecute->finalPosition.rowPosition] = moveNodeToExecute->piece;
    history_tail = moveNodeToExecute;
    history_tail = history_tail->next;
    handleEndTurn();
}
