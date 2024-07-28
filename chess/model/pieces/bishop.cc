#include "bishop.h"

Bishop::Bishop(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Bishop, board} {}

char Bishop::toChar() const {
    if (colour == Colour::Black) {
        return 'b';
    }
    else {
        return 'B';
    }
}

std::vector<Coordinate::Coordinate> Bishop::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    //MISSING IMPLEMENTATION

    return validMoves;
}

bool Bishop::canTargetSquare(Coordinate::Coordinate square) const {
    // Implementation goes here
}

bool Bishop::makeMove(Coordinate::Coordinate dest) {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
        return false;
    }

    position = dest;
    
    return true;
}
