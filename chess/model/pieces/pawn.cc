#include "pawn.h"

Pawn::Pawn(Coordinate position, Piece::Colour colour, Piece::PieceType pieceType, Board* board) 
    : PieceClonable{position, colour, pieceType, board}, hasMoved{false}, justMovedTwice{false} {}

Piece::PieceType Pawn::getPieceType() {
    // Implementation goes here
}

std::vector<Coordinate> Pawn::getValidMoves() {
    // Implementation goes here
}

bool Pawn::makeMove(Coordinate dest) {
    // Implementation goes here
}

bool Pawn::canTargetSquare(Coordinate square) {
    // Implementation goes here
}
