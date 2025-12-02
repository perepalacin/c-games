#include "../board/board.h"

void addMoveToHistory(PiecePosition initialPosition, PiecePosition finalPosition, Piece *movedPiede,
                      Piece *takenPiece);
void revertMove(void);
void forwardMove(void);
