#include "rook.h"

Rook::Rook(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Rook, board}, hasMoved{false} {}

char Rook::toChar() const {
    if (colour == Colour::Black) {
        return 'r';
    }
    else {
        return 'R';
    }
}

std::vector<Coordinate::Coordinate> Rook::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    //MISSING IMPLEMENTATION

    return validMoves;
}

bool Rook::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
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
