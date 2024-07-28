#include "knight.h"

Knight::Knight(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Knight, board} {}

std::vector<Coordinate::Coordinate> Knight::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    //MISSING IMPLEMENTATION

    return validMoves;
}

bool Knight::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
}

bool Knight::makeMove(Coordinate::Coordinate dest) {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
        return false;
    }

    position = dest;
    
    return true;
}
