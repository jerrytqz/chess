#include "pawn.h"

Pawn::Pawn(Coordinate::Coordinate position, Colour colour, Board* board) 
    : PieceClonable{position, colour, Piece::PieceType::Pawn, board}, hasMoved{false}, justMovedTwice{false} {}

std::vector<Coordinate::Coordinate> Pawn::getValidMoves() const {
    // Implementation goes here
}

bool Pawn::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
}

bool Pawn::makeMove(Coordinate::Coordinate dest) {
    // Implementation goes here
}
