#include "rook.h"
#include "../board.h"
#include <utility>

Rook::Rook(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Rook, board}, hasMoved{false} {}

std::vector<Coordinate::Coordinate> Rook::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    std::vector<std::pair<int, int>> directions = {{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    }};

    for (const auto& dir : directions) {
        int dRow = dir.first;
        int dCol = dir.second;
        for (int i = 1;; i++) {
            Coordinate::Coordinate nextPos{position.row + i * dRow, position.col + i * dCol};

            if (!Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
                break; //unable to move in this direction (edge of board)
            }

            std::unique_ptr<Piece> targetPiece = board->getPiece(nextPos);
            bool canCapture = targetPiece && targetPiece->getColour() != this->getColour();
            bool canMove = !targetPiece || canCapture;

            if (canMove) {
                validMoves.push_back(nextPos);

                if (canCapture) {
                    break; //stop moves in this direction after capturing a piece
                }
            } else {
                break; //stop moves in this direction (blocked by a piece)
            }
        }
    }

    return validMoves;
}

void Rook::adjustAfterMove(Coordinate::Coordinate) {
    hasMoved = true;
}

int Rook::getMovementData() {
    if (hasMoved)
        return 1;
    return 0;
}
