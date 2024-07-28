#include "queen.h"

Queen::Queen(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Queen, board} {}

char Queen::toChar() const {
    if (colour == Colour::Black) {
        return 'q';
    }
    else {
        return 'Q';
    }
}

std::vector<Coordinate::Coordinate> Queen::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    //MISSING IMPLEMENTATION

    return validMoves;
}

bool Queen::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
}

bool Queen::makeMove(Coordinate::Coordinate dest) {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
        return false;
    }

    position = dest;
    
    return true;
}
