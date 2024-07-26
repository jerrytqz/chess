#include "pawn.h"

Pawn::Pawn(Coordinate position, Colour colour, Board* board) 
    : PieceClonable{position, colour, Piece::PieceType::Pawn, board}, hasMoved{false}, justMovedTwice{false} {}

Piece::PieceType Pawn::getPieceType() const {
    // Implementation goes here
}

std::vector<Coordinate> Pawn::getValidMoves() const {
    // Implementation goes here
}

bool Pawn::canTargetSquare(Coordinate square) const {
    // Implementation goes here
}

bool Pawn::makeMove(Coordinate dest) {
    // Implementation goes here
}
