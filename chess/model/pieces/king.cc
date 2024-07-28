#include "king.h"

King::King(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::King, board}, hasMoved{false} {}

char King::toChar() const {
    if (colour == Colour::Black) {
        return 'k';
    }
    else {
        return 'K';
    }
}

std::vector<Coordinate::Coordinate> King::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    //MISSING IMPLEMENTATION

    return validMoves;
}

bool King::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
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
