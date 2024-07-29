#include "rook.h"
#include "../board.h"

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

    for (const auto& [dRow, dCol] : directions) {
        for (int i = 1;; ++i) {
            Coordinate::Coordinate nextPos{position.row + i * dRow, position.col + i * dCol};

            if (!Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
                break; //unable to move in this direction (edge of board)
            }

            if (board->getPiece(nextPos)) {
                if (board->getPiece(nextPos)->getColour() != this->getColour()) {
                    validMoves.push_back(nextPos); //capture piece
                }
                break; //stop moves in this direction
            }

            validMoves.push_back(nextPos); //empty square
        }
    }

    return validMoves;
}

bool Rook::canTargetSquare(Coordinate::Coordinate square) const {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), square) == validMoves.end()) { //square is not in valid moves
        return false;
    }
    else {
        return true;
    }
}

bool Rook::makeMove(Coordinate::Coordinate dest) {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
        return false;
    }

    hasMoved = true;
    position = dest;
    
    return true;
}
