#include "king.h"
#include "../board.h"
#include <utility>

King::King(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::King, board}, hasMoved{false} {}

std::vector<Coordinate::Coordinate> King::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    // Possible relative moves for a king
    std::vector<std::pair<int, int>> directions = {{
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    }};

    for (const auto& dir : directions) {
        Coordinate::Coordinate nextPos{position.row + dir.first, position.col + dir.second};

        // Check if the move is within bounds and doesn't leave the king in check
        if (Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
            std::unique_ptr<Piece> targetPiece = board->getPiece(nextPos);
            bool canMove = !targetPiece || targetPiece->getColour() != this->getColour();

            if (canMove) {
                validMoves.push_back(nextPos);
            }
        }
    }

    return validMoves;
}

bool King::makeMove(Coordinate::Coordinate dest) {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
        return false;
    }

    hasMoved = true;
    position = dest;
    
    return true;
}
